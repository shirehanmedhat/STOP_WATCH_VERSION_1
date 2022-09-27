/*
 ============================================================================
 Name        : WATCH.c
 Author      : Shirehan Medhat Abdelsalam Ali
 Description : Source file Of Mini Project 2
 ============================================================================
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "WATCH.h"
extern long unsigned int INTERRUPT_COUNTER;

//Initializing TIMER0
//OVER FLOW MOOD
void TIMER0_INIT_DELAY_3mseconds(void)
{
	TCCR0 = (1<<FOC0) | (1<<CS00) | (1<<CS02);
	TCNT0 =0;
	 while (TCNT0 !=3);
}
//Initializing TIMER 1
// CTC MOOD
void TIMER1_INIT (void)
{
	//FROM Data sheet
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<CS10) | (1<<CS12) | (1<<WGM12);
	TCNT1 =0;
	OCR1A = 1000;
	TIMSK = (1<<OCIE1A);
	SREG |= (1<<7);
}
//Initializing EXI0
//Falling edge

void EXI0_INIT(void)
{


	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);
	SREG |=(1<<7);
}

//Initializing EXI1
//rising edge
void EXI1_INIT(void)
{


	MCUCR |= (1<<ISC11)|(1<<ISC10);
	GICR |= (1<<INT1);
	SREG |=(1<<7);
}
//Initializing EXI1
//Falling edge
void EXI2_INIT(void)
{


	MCUCSR &= ~(1<<ISC2);
	GICR |= (1<<INT2);
	SREG |=(1<<7);
}

// convert from seconds to the Time from HH MM SS
void CONVERT_SECONDS_TO_TIME_FORM (char *PTR_TO_DATA_ARRAY)
{

	if (PTR_TO_DATA_ARRAY !=NULL)
	{


		unsigned long int temp= INTERRUPT_COUNTER;

		for (int counter =0 ; counter <6 ; counter++)
		{
			//To avoid Missing Hours Above 60 hour
			//Check TEST_1
			if ((counter ==4) && (temp>=60))
			{
				PTR_TO_DATA_ARRAY [counter] = temp %10;
				temp = temp /10;
				counter ++;
				PTR_TO_DATA_ARRAY [counter] = temp;
			}
			// For the hours below 60 hour ;
			else
			{
				//Separate the Part second / minute or hour part
				char signal = temp %60;
				//convert the result number to two separable digits
				PTR_TO_DATA_ARRAY [counter] = signal %10;
				signal = signal /10;
				counter ++;
				PTR_TO_DATA_ARRAY [counter] = signal;
				temp = temp/60;
			}
		}

	}


}
// Display the Time On the Seven Segment
void DISPLAY_TIME (char *PTR_TO_ARRAY)
{
	if (PTR_TO_ARRAY != NULL)
	{
		PORTA =0x01;
		PORTC = PTR_TO_ARRAY [SEC1Counter];
		TIMER0_INIT_DELAY_3mseconds ();
		PORTA =0x02;
		PORTC = PTR_TO_ARRAY [SEC2Counter];
		TIMER0_INIT_DELAY_3mseconds ();
		PORTA =0x04;
		PORTC = PTR_TO_ARRAY [MIN1counter];
		TIMER0_INIT_DELAY_3mseconds ();
		PORTA =0x08;
		PORTC = PTR_TO_ARRAY [MIN2counter];
		TIMER0_INIT_DELAY_3mseconds ();
		PORTA =0x10;
		PORTC = PTR_TO_ARRAY [HOUR1counter];
		TIMER0_INIT_DELAY_3mseconds ();
		PORTA =0x20;
		PORTC = PTR_TO_ARRAY [HOUR2counter];
		TIMER0_INIT_DELAY_3mseconds ();
	}

}

//INIT of the first 4-bits of PORTC
//Multiplexed Seven Segment INIT
void L7447N_INIT (void)
{
	DDRC = (DDRC & 0xf0) | 0x0f;
	PORTC = (PORTC & 0xf0) | 0x0f;
}
//Multiplexed Seven Segment control INIT

void SEGMENT_CONTROL_INIT (void)
{
	DDRA = (DDRA & 0xc0) | 0x3f ;
	PORTA = (PORTA & 0xc0) | 0x00;
}

// Initializing the PUSH BUTTONS
void PUSH_BUTTONS_INIT (void)
{
	//internal pull-up resistor
	DDRD &= ~(1<<2);
	PORTD |=(1<<2);
	//external pull-down resistor
	DDRD &= ~(1<<3);
	//internal pull-up resistor
	DDRB &= ~(1<<2);
	PORTB |=(1<<2);
}


