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
	enum dataType {INT,FLOAT};

private:
	dataType _type;
	int32_t *_op1;
	int32_t *_op2;
	int32_t *_res;
	float *_op1f;
	float *_op2f;
	float *_resf;	
public:	

	TimedCustomInst(std::string name): TimedModel(name) {_op1=0; _op2=0; _res=0;};
	~TimedCustomInst(){};

	// main run function
	SimulationTime Run();

	//SimulationTime SetUpf(float *op1, float *op2, float *res);
	SimulationTime SetUpFloat(int32_t *op1, int32_t *op2, int32_t *res);
	SimulationTime SetUp(int32_t *op1, int32_t *op2, int32_t *res);

	void Reset(){_op1=0; _op2=0; _res=0;};
};

#endif /* __UCUSTOMINST_H */
