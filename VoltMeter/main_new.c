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
			print_measured();

			if (header[i] != 0)
			{
				SBUF = header[i];
				i++;
			}
			else
			{
			/* This row is rellevant only when header[i] = 0 */
				FLAG = 0;	// Reset the FLAG	
			}

	   }
		
    if(ADCI)								// We have permissions from prof. Engelberg to do like this because it is a small program.
    {
        ADCI = 0; 
        is_voltage = calculate_voltage();
        SCONV = 1;
			
    }
	}
}

