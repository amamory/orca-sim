/** 
 * This part of project URSA. More information on the project
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
#ifndef __USIGNAL_SET_H
#define __USIGNAL_SET_H

//lib dependent includes
#include <iostream>
//#include <queue>
#include <vector>
#include <stdint.h>

//api includes
#include <UntimedModel.h>
#include <UMemory.h>

/**
 * The USignalSet class models a generic set of busses of type T.
 * */
template <typename T>
class USignalSet : public UntimedModel {

private:

    /** number of signals in the set. Cannot be changed runtime. **/
    uint32_t _num_signals;

	/** memory position of the first signal. Other signals' positions
     * are generated by incrementing this index by sizeof(T)**/
    MemoryAddr  _mem_addr;
    MemoryType* _mem_ptr;

    /** a pointer to the first signal. An array will be instantiated 
     * to store signals in that pointer. **/
    USignal<T>** _signals;
    
    /** an optional name to identify this model during runtime */
	std::string _t_name;
	
public:

    /**
     * @brief Constructor. Creates a new SignalSet.
     * @param name An arbitrary name for the instance.
     * @param nsig Number of signals to be created
     */
	 USignalSet(std::string name, uint32_t nsig);

    /**
     * @brief Destructor. 
     * @note DO NOT free _t_ptr by any means as this pointer must be 
     * freed by the class which allocated the space. 
     */
    ~USignalSet();

    /**
     * @brief Get the a signal from the set. 
     * @param index The identifier of the signal to be returned.
     * @return A pointer to the requested signal.
     */
    USignal<T>* GetSignal(uint32_t index);
	
    /**
     * @brief Maps the signal set to a given memory address. Signals'
     * addresses are generated by incrementing the address of the 
     * first signal.
     * @param mptr Pointer to the memory location to be mapped
     * @param addr Address to the set to the first signals
     */
    void MapTo(MemoryType* mptr, MemoryAddr addr);
};

//Some of the most used instances. More can be added later.
//for larger data size, consider using a UMemory instead.
template class USignalSet<bool>;  //wire
template class USignalSet<uint8_t>;  //mem word
template class USignalSet<uint16_t>; //dmni/noc word
template class USignalSet<uint32_t>; //proc word
template class USignalSet<uint64_t>; //double word
template class USignalSet<int8_t>;  //mem word
template class USignalSet<int16_t>; //dmni/noc word
template class USignalSet<int32_t>; //proc word
template class USignalSet<int64_t>; //double word


#endif /* USIGNAL_H */
