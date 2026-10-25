/*
Names: Matan Ronen & Matanel Kadosh
File: peripherals.c
ADC interrupt service routine implementing the FIR low-pass filter
(Chapter 22). Samples channel 0 of the ADC, outputs the raw sample to
DAC0, runs the filter (shift buffer + convolution with the coefficients
from coeffs.h), clamps a negative result to zero, and outputs the
filtered result to DAC1.
*/

#include <aduc841.h>
#include "peripherals.h"
#include "coeffs.h"          // N, NUM_COEFF, SCALE_FACTOR and the code array h[]

int idata buffer[NUM_COEFF]; // oldest sample at index 0, newest at NUM_COEFF-1

void ADC_ISR(void) interrupt 6
{
    unsigned char i;
    long int sum = 0;
    int new_sample = ADCDATA & 0x0FFF;     // only the lower 12 bits carry the sample

    ADCI = 0;
    DAC0 = new_sample;                     // raw, unfiltered sample

    for (i = 0; i < NUM_COEFF - 1; i++)    // shift the buffer left
    {
        buffer[i] = buffer[i + 1];
    }
    buffer[NUM_COEFF - 1] = new_sample;    // newest sample at the highest index

    for (i = 0; i < NUM_COEFF; i++)        // convolution sum
    {
        sum += (long int)h[i] * (long int)buffer[i];
    }
    sum /= SCALE_FACTOR;                   // undo the coefficient scaling

    if (sum < 0)
        sum = 0;                           // clamp negative output to zero

    DAC1 = (int)sum;                       // filtered output
}
