/*
Name: Matan Ronen & Matanel Kadosh
Date: 14.07.2026
Grader: ?
File: main.c
This file implement an IIR moving average filter on the data 
from channel 0 ADC. In DAC0 the output is the origin data,
and in DAC1 the output is the data after the filter.
*/
#include <aduc841.h>
#include <stdio.h>
#include "peripherals.h"

#define FILTER_LENGTH 50

long int sum = 0;
unsigned int filtered = 0;
unsigned int oldest;

void main(void)
{
	T2_Init();               // Initialize Timer 2 for ADC sampling rate
    ADC_Init();              // Initialize Analog-to-Digital Converter
    DAC_Init();              // Initialize Digital-to-Analog Converters
    GlobalINT();             // Enable global interrupts
    cbuffer_reset(&cbuffer); // Clear all values in the circular buffer
	
    while (1)
    {
        if (ADCflag) // Check if a new sample is ready
        {
            ADCflag = 0;  // Clear the flag for the next interrupt
            oldest = update_cbuffer(&cbuffer, newsample);  // Add the new sample to the buffer and retrieve the oldest sample
            sum = (sum - oldest) + newsample;  // Update the running sum (subtract oldest, add newest)
            filtered = sum / FILTER_LENGTH;    // Calculate the moving average
            DAC0DATA =  newsample;    // Output the raw signal to DAC0
            DAC1DATA = filtered;      // Output the filtered signal to DAC1
        }
    }
}