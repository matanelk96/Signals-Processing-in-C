/*
Name: Matan Ronen, Matanel Kadosh
Date: 
File: peripheralc.c
Description: A UART-based voltmeter. 
Reads up voltage from th ADC (channel 0) and convert it to millivolt (integers) 
and transmits the formatted result string back to the terminal.
*/

#include "VoltTimer3.h"
#include "peripherals.h"
#include <aduc841.h>

void main( void )
{
	init_Timer3();
	init_UART();
	ena_ints();
	set_ADC();
	
	while(1)
	{
			if (FLAG)		
			{
					// Prepare the string and reset the array index 'i' to 0
					print_measured(); 

					// Temporarily disable UART interrupts to prevent disruption
					// from incoming characters (like pressing 'm' again) during transmission
					ES = 0; 
					
					// Transmit the entire string sequentially until the Null terminator ('\0')
					while (header[i] != '\0')
					{
							SBUF = header[i];
							while(TI == 0);  // Wait for the hardware to finish transmitting the current character
							TI = 0;          // Manually clear the transmit interrupt flag
							i++;             // Move to the next character in the array
					}
					
					ES = 1;   // Re-enable UART interrupts for future receptions
					FLAG = 0; // Transmission complete, reset the FLAG
			}
			
			if(ADCI)
			{
					ADCI = 0; // Clear the ADC interrupt flag
					
					// Read the 12-bit ADC value from the data registers
					voltage = (ADCDATAH << 8) | ADCDATAL;
					voltage &= 0x0FFF; // Mask the upper 4 bits to ensure a valid 12-bit value
					
					is_voltage = calculate_voltage(); // Calculate volt_h and volt_l
					SCONV = 1; // Trigger the next single ADC conversion
			}
	}
}

