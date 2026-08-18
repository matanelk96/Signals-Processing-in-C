#include "aduc841.h"
#include "SetTimer2_ADC_DAC.h"

/*
 * Names: Matan Ronen & Matanel Kadosh
 * File: SetTimer2_ADC_DAC.c
 * Description:
 *   Peripheral initialization module for Timer 2, ADC, and DAC on ADuC841.
 */

/**
 * @brief Initializes Timer 2 in auto-reload mode to generate sampling clock.
 * @details Configures Timer 2 reload values RCAP2H and RCAP2L, clears overflow bit,
 *          and starts the timer running.
 */
void init_Timer2(void)
{
   T2CON = 0x00;   // Timer 2 control: 16-bit Auto-Reload mode
   RCAP2H = 0x07;  // High byte reload value for target ADC sampling frequency
   RCAP2L = 0xA3;  // Low byte reload value
   TH2 = RCAP2H;   // Load initial Timer 2 counter high byte
   TL2 = RCAP2L;   // Load initial Timer 2 counter low byte
   TF2 = 0;        // Clear Timer 2 overflow flag (must be explicitly cleared in software)
   TR2 = 1;        // Enable / Start Timer 2
}

/**
 * @brief Configures Analog-to-Digital Converter (ADC) registers.
 * @details Powers up ADC, sets Timer 2 overflow as trigger source, selects Channel 0.
 */
void setADC(void)
{
   ADCCON1 = 0xBA;
   CCONV = 1;      // Enable Timer 2 conversion trigger

   // ADCCON2: Select ADC Input Channel 0
   ADCCON2 &= 0xF0;
}

/**
 * @brief Configures Digital-to-Analog Converter (DAC) registers.
 * @details Sets 12-bit mode and sync output control on DACCON.
 */
void setDAC(void)
{
   DACCON = 0x19;
}
