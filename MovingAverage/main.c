/*
Name: Matan Ronen & Matanel Kadosh
Date: 14.07.2026
Grader: ?
File: main.c
This file implement an IIR moving average filter on the data 
from channel 0 ADC. In DAC0 the output is the origin data,
and in DAC1 the output is the data after the filter.
*/

#include "SetTimer2_ADC_DAC.h"
#include "peripherals.h"
#include <aduc841.h>
 
sfr16 DAC0 = 0xF9;           
sfr16 DAC1 = 0xFB;           
long int sum = 0;            
int x_old; 

void main( void )
{
	init_Timer2();
	setADC();
	setDAC();
	EA = 1;                         		// Enable global interrupts
	init_buffer(FILTER_TAPS);
	
	while(1)
	{
		if(FLAG)
		{
				EADC = 0;                       // ????? ?????? ?????? ?????
				FLAG = 0;                       // ????? ????
				x_old = update_buffer(x_new);   
				DACCON &= ~0x04;                // ????? ????? ?-DAC
				DAC0 = x_new;                   
				
				// ?????? ??????: ???? ?????? ???? ????? ????? ??????
				sum += ((long int)x_new - (long int)x_old); 
				
				DAC1 = (int) (sum/FILTER_TAPS);
				DACCON |= 0X04;                 // ????? ?????? ?-DAC
				EADC = 1;                       // ????? ??????
		}
	}
}

