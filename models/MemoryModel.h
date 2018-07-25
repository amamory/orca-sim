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
#ifndef __GENERIC_RAM_H
#define __GENERIC_RAM_H

//simulation API
#include <Process.h>

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <cstdint>

//Remeber: a memory is an arrays of int8_t...
#define MemoryType int8_t
#define MemoryAddr uint32_t

// For performance reasons, a memory is implemented as   
// a vector of bytes (uint8_t). So, we opt for do not    
// encapsulate it inside a class. Thus, memory manipu-   
// lation is done through the static methods of the
// MemoryHelper class.
class MemoryModel: public Process{

private:
  
    MemoryType* mem;
    std::string name;
    uint32_t length;
  
    //out ports
    uint32_t _data_read_a;
    uint32_t _data_read_b;
  
    //in ports
    uint32_t* _address_a;    //port A info
    bool*     _enable_a;
    uint8_t*  _wbe_a;
    uint32_t* _data_write_a;
    
    uint32_t* _address_b;    //port B info
    bool*     _enable_b;
    uint8_t*  _wbe_b;
    uint32_t* _data_write_b;
    
public:
    
    /** Creates a new memory area.	
     * @param size: Total length of the memory are to be created.
     * @param wipe (optional): If <true> is passed, wipes the are after creating. */
    MemoryModel(std::string name, 	uint32_t size, bool wipe = false);
    MemoryModel(std::string name, uint32_t size, bool wipe, std::string binname);

    /** Writes data to a given memory location.
     * @param addr: Location to write to.
     * @param data: Pointer to the place that hold the data to be copied to the memory.
     * @param length: Length of the data to be copied into the memory location. */
    void Write(uint32_t addr, MemoryType* data, uint32_t length);

    /** Reads data from a given memory location. 
      * @param addr: Location to read from.
      * @param buffer: Buffer to where the read data will be copied.
      * @param length: Length of the data that will be copyied from memory to 
           the buffer. */
    void Read (uint32_t addr, MemoryType* buffer, uint32_t length);
		
    /** Loads the content of a given file to the memory. File contents are
           treated as binaray data.
      * @param filename: Name of the file to be read.
      * @param location: Location of the memory area in which the contents of 
           the loaded file will be put. */
    void LoadBin(std::string filename, uint32_t size, uint32_t addr = 0);
		
    /** Write zeros to the whole memory area.
      * @param base: Starting address of the region to be wiped.
      * @param length: Number of memory positions to be overwritten. */
	void Wipe(uint32_t base, uint32_t length);
		
	/** Push the content of a memory are into sdtout.
	  * @param base: Initial address to start reading.
	  * @param size: Total length to be dumped. */
	void Dump(uint32_t base, uint32_t length);
	
	/** Overrides operator [] for accessing internal mem data
	  * @param i: index of the internal array to be accessed
	  * @return the element stored in the given index */
	MemoryType &operator[](int i) {
	
		//TODO: validate behaviour
		return this->mem[i];
	}
	
	//TODO:remove it as soon as possible
	MemoryType* GetMemPtr();
    
    //getters
    uint32_t* GetDataReadA();
    uint32_t* GetDataReadB();
    
    //portmap for memory ports
    void PortMapA(
        uint32_t* address_a, //port A info
        bool*     enable_a,
        uint8_t*   wbe_a,
        uint32_t* data_write_a
    );
    void PortMapB(
        uint32_t* address_b, //port B info
        bool*     enable_b,
        uint8_t*   wbe_b,
        uint32_t* data_write_b
    );
    
    //process impl
    unsigned long long Run(){
        //TODO: to be implemented
        return 1;
    }
};

#endif