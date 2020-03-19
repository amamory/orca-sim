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
 
#include "int-mult.h"

// uint_32 multiplier
#define MULT_RESULT		 (volatile uint32_t*)0xf000010C
#define MULT_OP1		 (volatile uint32_t*)0xf0000110
#define MULT_OP2		 (volatile uint32_t*)0xf0000114

uint32_t mult(const uint32_t op1, const uint32_t op2){
	*MULT_OP1 = op1;
	*MULT_OP2 = op2;
	return *MULT_RESULT;
} 

void int_mult(void){
    uint32_t op1; 
    uint32_t op2; 
    uint32_t out_external_mult;
	uint32_t out_internal_mult;
	int i=0;

	op1 = 10;
	op2 = 5;

    while (i<50){
		out_external_mult = mult(op1, op2); 
		out_internal_mult = op1*op2;

		printf("Result: %d x %d = %d == %d\n", op1, op2, out_external_mult, out_internal_mult);
		//printf("Result: %X x %X = %X == %X\n", &op1, &op2, &out_external_mult, &out_internal_mult);

		op2 += 1;

		delay_ms(1);
		i++;
	}

	hf_kill(hf_selfid());
}
