/*
Name: Matan Ronen & Matanel Kadosh
File: peripherals.h
Header file for the UART adding machine.
*/


void init_UART(void);
void ena_ints(void);
void print_measured(void);
void set_ADC( void );
int calculate_voltage(void);

extern long int voltage;
extern int is_voltage;
extern char k;
extern char i;
extern char header[25];
extern char FLAG;
extern unsigned int volt_h;                // High part of voltage measurement
extern unsigned int volt_l;                // Low part of voltage measurement

