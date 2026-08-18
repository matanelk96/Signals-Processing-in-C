#include <aduc841.h>
#include "SetTimer2_ADC_DAC.h"

/*
File: SetTimer2_ADC_DAC.c
Peripheral initialization for Timer2 (ADC sample clock), ADC, and DAC.
Timer2 reload value below targets Fs = 1kHz, matching the placeholder
coefficients in coeffs.h -- recompute RCAP2H/L if you regenerate coeffs.h
for a different Fs (reload = 65536 - round(11059200 / Fs)).
*/

void init_Timer2(void)
{
    T2CON = 0x00;   // Timer2, 16-bit auto-reload, timer mode
    RCAP2H = 0xD4;  // Reload value for Fs = 1kHz
    RCAP2L = 0xCD;
    TH2 = RCAP2H;   // Load TH2:TL2 initially -- required before the first overflow
    TL2 = RCAP2L;
    TF2 = 0;
    TR2 = 1;
}

void setADC(void)
{
    ADCCON1 = 0xBA;  // ADC on, on-chip Vref, T2C=1 (Timer2 clocks the ADC)
    CCONV = 1;       // continuous conversion, triggered by Timer2 overflow
    ADCCON2 &= 0xF0; // channel 0
    EADC = 1;        // enable the ADC interrupt
}

void setDAC(void)
{
    DACCON = 0x19;   // 12-bit mode, DAC0/DAC1 range = VREF, both powered on
}
