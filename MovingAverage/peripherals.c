/*
Name: Matan Ronen & Matanel Kadosh
File: peripherals.c
Peripherals file for the IIR moving average machine.
*/

#include <ADUC841.h>
#include "peripherals.h"

#define FILTER_TAPS 50

bit FLAG = 0;
int x_new; 
sfr16 ADCDATA = 0xD9;


xdata circular_buffer CircularBuffer;	//We didn't do a ptr because there is only 1 buffer in this program.

// ADC interrupt service routine
static void ADC_ISR(void) interrupt 6
{
    x_new = ADCDATA;                // Read ADC data into x_new variable
    FLAG = 1;                  		// Set ADC interrupt flag
}


void init_buffer(unsigned char length)
{
	int i = 0;
	CircularBuffer.length = length;
	CircularBuffer.oldest_index = 0;
	
	for (i; i < CircularBuffer.length; i++)
	{
		CircularBuffer.samples[i] = 0;
	}
}

// Update circular buffer with new sample
int update_buffer(int x_new)
{
    int x_old = CircularBuffer.samples[CircularBuffer.oldest_index];   // Store old value from circular buffer
    CircularBuffer.samples[CircularBuffer.oldest_index] = x_new;       // Update circular buffer with new sample
    if (CircularBuffer.oldest_index < CircularBuffer.length - 1)
    {
        CircularBuffer.oldest_index++;                       		  // Increment index if within bounds
    }
    else
    {
        CircularBuffer.oldest_index = 0;                     		 // Reset index to 0 if at end of buffer
    }
    return x_old;                          						     // Return old value
}


