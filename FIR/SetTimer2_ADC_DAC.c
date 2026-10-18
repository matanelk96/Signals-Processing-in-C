/*
Names: Matan Ronen & Matanel Kadosh
File: SetTimer2_ADC_DAC.c
Peripheral initialization for Timer2 (ADC sample clock), ADC, and DAC.

The Timer2 reload value targets Fs = 1 kHz, matching the placeholder
coefficients in coeffs.h. If coeffs.h is regenerated for a different Fs,
recompute the reload: reload = 65536 - round(11059200 / Fs)
(fir_design.py prints the RCAP2H/RCAP2L values to use).
*/

#include <aduc841.h>
#include "SetTimer2_ADC_DAC.h"

sfr16 RCAP2 = 0xCA;   // RCAP2L = 0xCA, RCAP2H = 0xCB
sfr16 T2    = 0xCC;   // TL2 = 0xCC,    TH2 = 0xCD

void init_Timer2(void)
{
    T2CON = 0x00;       // Timer2, 16-bit auto-reload, timer mode
    RCAP2 = 0xD4CD;     // reload for Fs = 11059200 / (65536 - 0xD4CD) = 1 kHz
    T2 = RCAP2;         // load TH2:TL2 now - the reload only happens after the first overflow
    TF2 = 0;
    TR2 = 1;
}

void setADC(void)
{
    ADCCON1 = 0xBA;     // ADC on, on-chip Vref, T2C = 1 (Timer2 overflow starts a conversion)
    CCONV = 1;          // continuous conversion
    ADCCON2 &= 0xF0;    // channel 0
    EADC = 1;           // enable the ADC interrupt
}

void setDAC(void)
{
    DACCON = 0x19;      // 12-bit mode, DAC0/DAC1 range = VREF, both DACs on
}
