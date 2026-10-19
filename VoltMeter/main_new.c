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
				TI = 1;						//handle UART interrupt
				FLAG = 0;					// Reset the FLAG
	   }
		
    if(ADCI)								// We have permissions from prof. Engelberg to do like this because it is a small program.
    {
        ADCI = 0; 
        is_voltage = calculate_voltage();
        SCONV = 1;
			
    }
	}
}

