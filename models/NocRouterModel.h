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
#ifndef __NOC_ROUTER_MODEL_H
#define __NOC_ROUTER_MODEL_H

//std API
#include <iostream>

//simulator API
#include <Process.h>
#include <Buffer.h>

//model API
#include <MemoryModel.h>

enum class RouterState{
    WORMHOLE, ROUNDROBIN
};

//routing ports
#define SOUTH 3
#define NORTH 1
#define WEST  2
#define EAST  4
#define LOCAL 0

class NocRouterModel: public Process {

private:
        uint32_t _round_robin;
        uint32_t _packets_to_send;
        uint32_t _target_port, _source_port;
        
        //address of the router
        uint32_t _x;
        uint32_t _y;
        
        //state
        RouterState _state;
        
        //output buffers
        Buffer _ob[5];
        
        //input buffers
        Buffer* _ib[5];        
public: 
        /**
         * @brief Get a pointer to one of the output buffers.
         * @param p The port to where the pointer will be pointing.
         * @return The pointer to the respective buffer. */
        Buffer* GetOutputBuffer(uint32_t p);
        
        //port map
        void PortMap(
            Buffer* ib_south, 
            Buffer* ib_north, 
            Buffer* ib_local, 
            Buffer* ib_west, 
            Buffer* ib_east
        );
        
		/** Implementation of the Process' interface
		  * @return time taken for perming next cycle */
		unsigned long long Run();
		
		
		NocRouterModel(string name, uint32_t x_pos, uint32_t y_pos);
	
		/** Dtor. */
		~NocRouterModel();
		
		void Reset();
};


#endif /* DMNI */
