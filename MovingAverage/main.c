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
            FLAG = 0;                      // Reset the sample flag
            x_old = update_buffer(x_new);  // Update buffer with new value
						DACCON &= ~0x04;				   // Do not output the data in the DACs yet (clear sync bit only)
            DAC0 = x_new;                  // Update DAC0 with new value
            sum += (x_new - x_old);        // Update sum with difference
            DAC1 = (int) (sum/FILTER_TAPS);        // Update DAC1 with averaged sum
						DACCON |= 0X04; 			   // Output the data in the DACs synchronizely
        }
	}
}

