/** 
 * This file is part of project URSA. More information on the project
 * can be found at 
 *
 * URSA's repository at GitHub: http://https://github.com/andersondomingues/ursa
 *
 * Copyright (C) 2018 Anderson Domingues, <ti.andersondomingues@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. **/
#ifndef __TDMAMULT_H
#define __TDMAMULT_H

//std API
#include <iostream>

//simulator API
#include <TimedModel.h>
#include <UMemory.h>
#include <USignal.h>

//NN memory configuration. TOTAL_NN_MEM_SIZE and SIMD_SIZE can be changed in design time
#define TOTAL_NN_MEM_SIZE   	4 * 1024 * 1024 					///< this is the maximum memory address space to be used for operands of the MACs 
#define SIMD_SIZE     			32   								///< max number of parallel MAC operations
#define NN_MEM_SIZE_PER_CHANNEL (TOTAL_NN_MEM_SIZE / 2)  /  SIMD_SIZE ///< the max amount of data per channel 
#define MEMW_BASE 				0x40500000     						///< the base address to store the weights
#define MEMI_BASE 				MEMW_BASE + (TOTAL_NN_MEM_SIZE/2)	///< the base address to store the inputs

/*
 The current approach is: the cpu copies data to the DMA memory, configure the DMA, stall the CPU, does MACs in parallel and in burst mode, 
 copies the MAC results to MMIO, release the stall, and the CPU copies the results and cotinue the software.

 An alternative approach, interesting if we have multiple tasks and OS, is not to halt the CPU, letting other tasks using the CPU while
 the DMA is working. When the DMA finishes, and interrupt is asserted, and the results are copied back to the software layer.
*/
enum class DmaState{
	WAIT_CONFIG_STALL, ///< wait cpu to configure the DMA, indicated by _sig_dma_prog.  Then, the DMA raises _sig_stall to stall the cpu while the DMA is working.
	COPY_FROM_MEM,     ///< copy content from the NN memory to the MAC internal operand registers.
	COPY_TO_CPU,       ///< just waste a cycle to copy the MAC results to the MMIO.
	FLUSH              ///< deassert the _sig_stall, returning to the wait mode. The CPU returns to activity.
};

/**
 * @class TDmaMult
 * @author Alexandre Amory, based on Anderson's  TDMANetif
 * @date 01/04/20
 * @file TDmaMult.h
 * @brief DMA unit reponsible to transfer weight and input data from the NN memory 
 *	 directly to the vector MACs
 */
class TDmaMult: public TimedModel{

private:
	/// pointer to the main memory
	UMemory* _mem0;
	/// base address of the weight memory channel. Once set, it does not change in runtime. it can only be changed in design time.
	uint32_t _memW[SIMD_SIZE];
	/// base address of the input memory channel. Once set, it does not change in runtime. it can only be changed in design time.
	uint32_t _memI[SIMD_SIZE];
	/// base address to the array with the results from the MAC units. Supposed to be constant. it can only be changed in design time.
	uint32_t _base_mac_out_addr;
	/// States for DMA process.
    DmaState _dma_state;
    
	///@{
	/// control signals.
	USignal<uint8_t>*  _sig_stall;      ///< (OUT): stalls cpu while the DMA is copying from the memories.
	USignal<uint8_t>*  _sig_dma_prog;   ///< (IN): processor writes 1 to start the DMA.
	///@}

	///@{
    /// data sent from the processor to program the DMA.
	USignal<uint32_t>* _sig_burst_size; ///< IN: number of MACs ops to be executed in burst mode.
	USignal<uint32_t>* _sig_nn_size;  	///< IN: (not used) amount of memory configured for each channel. 1 means NN_MEM_SIZE_PER_CHANNEL bytes, 2 means 2*NN_MEM_SIZE_PER_CHANNEL bytes, ...
	USignal<uint32_t>* _sig_out_size;   ///< IN: (not used) number of expected output data. 
	///@}

	///@{
    /// internal registers between the pipeline stages.
	float  _op1[SIMD_SIZE], _op2[SIMD_SIZE];  ///< data 'register' pf the 1st pipeline stage, i.e. the operands of the MAC units.
	float  _reg_mul[SIMD_SIZE];  ///< data 'register' between the 2nd and the 3rd pipeline stages. The result of the multiplication.
	float  _reg_mac[SIMD_SIZE];  ///< data 'register' with the output of the MAC.
	///@}

	///@{
	/// pipeline signals.
	uint8_t _mul_loaded; ///< signal between the 1st and the 2nd pipeline stages.
	uint8_t _mul_ready;  ///< signal between the 2nd and the 3rd pipeline stages.
	///@}

	///@{
	/// internal data register. Data sent from the processor to program the DMA.
	uint32_t _burst_size;       ///< total number of multiplications.
	uint32_t nn_size;           ///< (not used) number of NN memory banks for a single MAC.
	uint32_t out_size;   		///< (not used) number of expected output data.
	//others 
	uint32_t _remaining;        ///< count number of data to be read.
	/// memory idx used to access both the input and weight memories.
	uint32_t _mem_idx;

	///@}

	///@{
    /// Internal processes -- 3 stage pipeline.
    void ReadData();	///< 1st pipeline stage, i.e. data fetch
	void DoMult();		///< 2nd pipeline stage, multiplication
	void DoAcc();		///< 3rd pipeline stage, accumulation

public:	
    
    //getters
	DmaState GetDmaState();

    //other 
    SimulationTime Run();
    void Reset();

    /** ctor
     * @param name: name of the module.
	 * @param stall: signal to stall the processor while the DMA is going on.
     * @param burst_size: MMIO with the total number of multiplications.
     * @param nn_size: (not used) number of NN memory banks for a single MAC.
	 * @param out_size: (not used) number of expected output data.
	 * @param base_mac_out_addr: base address to the array with the output of the MACs.
	 * @param mac: pointer to the MAC module.
	 * */
    TDmaMult(string name, USignal<uint8_t>* stall, USignal<uint8_t>* dma_start, USignal<uint32_t>* burst_size, 
		USignal<uint32_t>* nn_size, USignal<uint32_t>* out_size, uint32_t base_mac_out_addr, UMemory* main_mem);
		
	/** dtor
	 * */
    ~TDmaMult();
};


#endif /* __TDMAMULT_H */
