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
#ifndef __UCUSTOMINST_H
#define __UCUSTOMINST_H

//api includes
#include <TimedModel.h>

/**
 * This class models an external (memory-mapped) combinational FP multipler
 * TODO: does it work with signed values ?!?!
 */
class TimedCustomInst : public TimedModel{ 

private:
	float _op1;
	float _op2;
	float *_res;
public:	

	TimedCustomInst(std::string name): TimedModel(name) {_op1=0; _op2=0; _res=0;};
	~TimedCustomInst(){};

	// main run function
	SimulationTime Run();

	//SimulationTime SetUp(float op1=0.0, float op2=0.0, float *res=0);
	SimulationTime SetUp(float op1, float op2, float *res);

	void Reset(){_op1=0; _op2=0; _res=0;};
};

#endif /* __UCUSTOMINST_H */
