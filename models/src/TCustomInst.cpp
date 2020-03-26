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

#include <TCustomInst.h>

SimulationTime TimedCustomInst::Run() {
    *_res = *(_op1) * *(_op2);
    //printf("XXXXXXXXXXXXXXXXXX GetResultInt   %d x %d = %d\n", _op1.i, _op2.i, res.i);
    //printf("XXXXXXXXXXXXXXXXXX GetResultFloat %.8f x %.8f = %.8f\n", _op1.f, _op2.f, res.f);
    return 1; //takes only 1 cycle to execute this operation
};

// at least one operand is mandatory
//SimulationTime TimedCustomInst::SetUp(float op1=0.0, float op2=0.0, float *res=0){
SimulationTime TimedCustomInst::SetUp(int32_t *op1, int32_t *op2, int32_t *res){
    _op1 = op1;
    _op2 = op2;
    _res = res;
    return Run();
}


