
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

#include <UMult.h>


uint32_t UntimedFPMultiplier::GetResult() {
    union DataMult res;
    res.f = _op1.f*_op2.f;
    //printf("XXXXXXXXXXXXXXXXXX GetResultInt   %d x %d = %d\n", _op1.i, _op2.i, res.i);
    //printf("XXXXXXXXXXXXXXXXXX GetResultFloat %.8f x %.8f = %.8f\n", _op1.f, _op2.f, res.f);
    return res.i ;
};


uint32_t UntimedIntMultiplier::GetResult() {
    uint32_t res;
    res = _op1*_op2;
    //printf("XXXXXXXXXXXXXXXXXX GetResultInt   %d x %d = %d\n", _op1, _op2, res);
    return res ;
};
