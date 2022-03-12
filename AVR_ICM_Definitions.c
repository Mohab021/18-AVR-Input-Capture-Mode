
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_ICM_Declarations.h"

void ICM_Initialize()
{
	TCCR1A = 0x00; //clear
	TCNT1 = 0x00; //clear counter-timer 1 register
	TIFR |= (1<<ICF1); //clear ICF1 (Input Capture Flag of Timer 1)
}

uint16_t ICM_Rising_Edge()
{
	uint16_t t;
	
	TCCR1B = 0x41; //0b01000001 rising edge, normal mode ,no pre-scaler
	while ( !(TIFR & (1<<ICF1)) ) ; //wait until the capture occurs
	
	//edge has arrived
	t = ICR1;
	TIFR |= (1<<ICF1); //clear ICF Flag
	return t;
}

uint16_t ICM_Falling_Edge()
{
	uint16_t t;
	
	TCCR1B = 0x01; //0b00000001 falling edge, normal mode ,no pre-scaler
	while ( !(TIFR & (1<<ICF1)) ) ; //wait until the capture occurs
	
	//edge has arrived
	t = ICR1;
	TIFR |= (1<<ICF1); //clear ICF Flag
	return t;
}

void ICM_Stop()
{
	TCCR1B = 0x00; //stop the timer1
}
