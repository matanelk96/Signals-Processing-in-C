/*
Name: Matan Ronen & Matanel Kadosh
File: main.c
Chapter 22 lab: a simple FIR low-pass filter.
ADC channel 0 is sampled at a rate set by Timer2. DAC0 outputs the raw
sample, DAC1 outputs the filtered sample (or zero, if the filter output
would have been negative). All the filtering work happens in the ADC
interrupt (ADC_ISR, in peripherals.c) -- main() just initializes the
peripherals and idles.
*/

#include "SetTimer2_ADC_DAC.h"
#include "peripherals.h"
#include <aduc841.h>

void main(void)
{
    init_Timer2();
    setADC();
    setDAC();
    EA = 1;

    while (1) {}
}
