/*
 * Implementation file for EXAMPLE-COUNTERS application.
 * Copyright (C) 2018-2019 Anderson Domingues, <ti.andersondomingues@gmail.com>
 * This file is part of project URSA (http://https://github.com/andersondomingues/ursa).
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
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */
 
#include "float-mult.h"

#define MULT_RESULT		(*(uint32_t *)0xf0000100)
#define MULT_OP1		(*(uint32_t *)0xf0000104)
#define MULT_OP2		(*(uint32_t *)0xf0000108)


float mult(const float op1, const float op2){
	MULT_OP1 = op1;
	MULT_OP2 = op2;
	return MULT_RESULT;
}


//Task for printing values store by CPU counters. 
void float_mult(void){
    float op1; 
	float op2_copy; 
    float op2; 
    float out_buggy; 
	float out_ok;

	int8_t sop1[10];
	int8_t sop2_copy[10];
	int8_t sop2[10];
	int8_t sout_buggy[50];
	int8_t sout_ok[50];

	int i=0;

	op1 = 10;
	op2 = 5;


    while (i<50){
		ftoa(op1,sop1,2);
		ftoa(op2,sop2,2);
		out_buggy = mult(op1, op2); 
		// se estivesse correto, o valor de f2_copy == f2. f2_copy está truncado !
		op2_copy = MULT_OP2;
		i= ftoa(op2_copy,sop2_copy,2);
	
		// esse resultdo da correto
		out_ok = op1*op2;
		ftoa(out_buggy,sout_buggy,6);
		ftoa(out_ok,sout_ok,6);

		printf("Result: %s x %s = %s != %s\n", sop1, sop2, sout_buggy, sout_ok );
		printf("Result: %s = %s\n", sop2, sop2_copy );

		op2 += 0.1;

		//add some delay to avoid flooding the network
		delay_ms(1);
		i++;
	}

	hf_kill(hf_selfid());
}
