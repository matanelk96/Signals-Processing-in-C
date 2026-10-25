/*
Names: Matan Ronen & Matanel Kadosh
File: peripherals.h
Header file for the FIR low-pass filter lab (Chapter 22).

Holds only the 16-bit SFR declarations used by the ADC interrupt. The filter
coefficients (coeffs.h) are deliberately NOT included here: coeffs.h defines
the `code` array h[], so it must be included by exactly one .c file
(peripherals.c) or the linker would see two copies of h[].
*/

#ifndef PERIPHERALS_H
#define PERIPHERALS_H

sfr16 ADCDATA = 0xD9;   // ADCDATAL = 0xD9, ADCDATAH = 0xDA
sfr16 DAC0    = 0xF9;   // DAC0L = 0xF9,    DAC0H = 0xFA
sfr16 DAC1    = 0xFB;   // DAC1L = 0xFB,    DAC1H = 0xFC

#endif
