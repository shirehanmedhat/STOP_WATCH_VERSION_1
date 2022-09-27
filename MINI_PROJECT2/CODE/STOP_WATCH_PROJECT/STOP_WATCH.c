/*
 ============================================================================
 Name        : STOP_WATCH.c
 Author      : Shirehan Medhat Abdelsalam Ali
 Description : Source Code Main Of Mini Project 2
 ============================================================================
 */
//Calling Some AVR Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include "WATCH.h"
// variable to count number of the seconds
long unsigned int INTERRUPT_COUNTER= TEST_NORMAL_FROM_ZERO;
// INTERRUPT SERVES ROUTUNE OF TIMER1 OVER FLOW MOOD
ISR (TIMER1_COMPA_vect)
{

	// The Max Time is 99 Hour 59 Min 59 Sec then Over Flow Occurs
	if (INTERRUPT_COUNTER != 359999)
	{
		INTERRUPT_COUNTER ++;
	}
	else
	{
		INTERRUPT_COUNTER =0;
	}
	TIFR |= (1<<OCF1A);

}
// INTERRUPT SERVES ROUTUNE OF EXTERNAL INTERRUPT0
//SET
ISR (INT0_vect)
{

	INTERRUPT_COUNTER=0;

	GIFR |=(1<<INTF0);
}

// INTERRUPT SERVES ROUTUNE OF EXTERNAL INTERRUPT1
//STOP
ISR (INT1_vect)
{

	TCCR1B &=~ (1<<CS10);
	TCCR1B &=~ (1<<CS12);

	GIFR |=(1<<INTF1);
}

// INTERRUPT SERVES ROUTUNE OF EXTERNAL INTERRUPT2
//RESUME
ISR (INT2_vect)
{

	TCCR1B |= (1<<CS10) | (1<<CS12);
	GIFR |=(1<<INTF2);
}



int main (void)
{
	//Array to BE PASSED TO THE FUNCTIONS
	char ArrayForTime [6] = {0};
	// initialization of TIMER 1
	TIMER1_INIT ();
	// initialization of EX0
	EXI0_INIT ();
	// initialization of EX1
	EXI1_INIT ();
	// initialization of EX2
	EXI2_INIT ();
	////Multiplexed Seven Segment INIT
	L7447N_INIT ();
	// Initialization of the control pins on 7- segment
	SEGMENT_CONTROL_INIT ();
	//Initialization of PUSH BUTTONS
	PUSH_BUTTONS_INIT ();

	while (1)
	{
		DISPLAY_TIME (ArrayForTime);
		CONVERT_SECONDS_TO_TIME_FORM (ArrayForTime);
	}
	return 0;
}


