
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h> //for itoa() function
#include "AVR_Ports.h"
#include "AVR_LCD_Declarations.h"
#include "AVR_ICM_Declarations.h"

int main(void)
{
	uint16_t r1,f1,r2,high_pulse,period;
	char frequency[22], duty_cycle[12]; //string for LCD printing
	float duty_ratio;
	long int freq;
	
	LCD_Initialize();
	
	ICM_Initialize(); //initialize the input capture mode of the timer1
	r1 = ICM_Rising_Edge(); //capture the next rising edge
	f1 = ICM_Falling_Edge(); //capture the next falling edge
	r2 = ICM_Rising_Edge(); //capture the next rising edge
	ICM_Stop(); //stop the timer1
	
	while(1)
	{
		LCD_Clear();
		
		high_pulse = f1 - r1; //high pulse of the period
		period = r2 - r1; //one period = (the second rising edge) - (the first rising edge)
		
		freq = (F_CPU) / (period); //calculate frequency based on CPU clock rate
		duty_ratio = (((float) high_pulse) / ((float) period)) * 100; //duty cycle
	
		itoa(freq, frequency, 10); //10 for decimal base
		itoa((int)duty_ratio, duty_cycle, 10); //10 for decimal base
		
		LCD_Print_xy(0, 0, "Freq: ");
		LCD_Print(frequency);
		LCD_Print(" Hz");
		
		LCD_Print_xy(1, 0, "Duty Ratio: ");
		LCD_Print(duty_cycle);
		LCD_Print(" %");
		
		_delay_ms(500);
	}
}
