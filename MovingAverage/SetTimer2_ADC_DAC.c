#include "aduc841.h"
#include "SetTimer2_ADC_DAC.h"

/*
 * Names: Matan Ronen & Matanel Kadosh
 * File: SetTimer2_ADC_DAC.c
 * Timer 2, ADC and DAC setup. Target: 5 kHz sampling.
 * Reload = 65536 - round(11059200 / 5000) = 0xF75C (actual 4999.6 Hz).
 */

void init_Timer2(void)
{
   T2CON = 0x00;   // Auto-reload, timer mode
   RCAP2H = 0xF7;  // Reload value, high byte
   RCAP2L = 0x5C;  // Reload value, low byte
   TH2 = RCAP2H;   // Initial load
   TL2 = RCAP2L;
   TF2 = 0;        // Clear overflow flag
   TR2 = 1;        // Start Timer 2
}

void setADC(void)
{
   ADCCON1 = 0xBA;  // ADC on, Vref internal, Timer 2 starts conversions
   CCONV = 1;       // Continuous conversion
   ADCCON2 &= 0xF0; // Channel 0
   EADC = 1;        // Enable ADC interrupt
}

void setDAC(void)
{
   DACCON = 0x19;   // 12-bit, range VREF, sync bit cleared
}
