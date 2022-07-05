/**************************************************************************//**
 * @file     rtl8721dlp_rand2.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device Series
 * @version  V1.08
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2011 - 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#include "basic_types.h"
#include "ameba_soc.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __SYSTEM_CLOCK    PLATFORM_CLOCK

unsigned int rand_x = 123456789;

u32 Rand2(void)
{
	static unsigned int y = 362436;
	static unsigned int z = 521288629;
	static unsigned int c = 7654321;

	unsigned long long t, a= 698769069;

	rand_x = 69069 * rand_x + 12345;
	y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5);
	t = a * z + c; c = (t >> 32); z = t;

	return rand_x + y + z;
}

u32 Rand3(u32 seed)
{
	static unsigned int y = 362436;
	static unsigned int z = 521288629;
	static unsigned int c = 7654321;

	unsigned long long t, a= 698769069;

	rand_x = 69069 * rand_x + 12345 + seed;
	y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5);
	t = a * z + c; c = (t >> 32); z = t;

	return rand_x + y + z;
}
