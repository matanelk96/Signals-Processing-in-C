/*
Name: Matan Ronen, Matanel Kadosh
Date: 
File: peripheralc.c
Description: A UART-based voltmeter. 
Reads up voltage from th ADC (channel 0) and convert it to millivolt (integers) 
and transmits the formatted result string back to the terminal.
*/			
#include <aduc841.h>
#include "peripherals.h"
#include <stdio.h>

char k = '0';	//The Input from user
char i = '0';//Index of the header
char header[35];
char row_down[3];
unsigned int volt_h;                // High part of voltage measurement
unsigned int volt_l;                // Low part of voltage measurement
char FLAG = 0;
long int voltage;
int is_voltage = 0;


void UART( void ) interrupt 4
	/* the heavy code which is calculate the result is occured out of the interuupt*/
{
	FLAG = 1;
}

void init_UART( void )
{
	ES =1;
	SM1 = 1;					// :D
	REN = 1;					// :D
}

void ena_ints( void )
{
	EA = 1;
}

void set_ADC( void )
{
	ADCCON1 = 0XB8;  // 10111000	
	SCONV = 1;			 // Single conversion
	ADCCON2 &= 0XF0; // Channel 0
}

void print_measured( void )
{
	if (k != 'm' && k != 'M')
	{
		return;
	}
	i = 0;//reset the index
	if (is_voltage)
	{
		sprintf(header, "The measured voltage is %d.%03d. \n\r", volt_h, volt_l);
		TI = 1;
		is_voltage = 0;
	}
}


int calculate_voltage( void )
{
	 
	 //Storing the voltage (in millivolt) value in in 2 diffrent variables for the sprintf
   voltage *= 61035;
   volt_h = voltage / 100000000;
   volt_l = (voltage % 100000000) / 100000;

	return 1;
}






