/*
 * Names: Matan Ronen & Matanel Kadosh
 * File: SetTimer2_ADC_DAC.h
 * Description:
 *   Header file declaring initialization routines for Timer 2, ADC, and DAC peripherals.
 */

#ifndef SET_TIMER2_ADC_DAC_H
#define SET_TIMER2_ADC_DAC_H

/**
 * @brief Initializes Timer 2 in 16-bit Auto-Reload mode for ADC sampling clock generation.
 */
void init_Timer2(void);

/**
 * @brief Initializes ADuC841 ADC control registers (ADCCON1, ADCCON2).
 */
void setADC(void);

/**
 * @brief Initializes ADuC841 DAC control register (DACCON).
 */
void setDAC(void);

#endif // SET_TIMER2_ADC_DAC_H
