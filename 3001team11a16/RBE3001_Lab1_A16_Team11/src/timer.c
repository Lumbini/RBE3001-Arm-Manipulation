/**
 * timer.c
 *
 * @author Evan Bosia
 * @author Lumbini Parnas
 */

#include "RBELib/RBElib.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * @brief Initializes the specified timer in the specified mode. This
 * header file provides constants for NORMAL operation mode and
 * CTC operation mode, however there are many more modes of operation
 * for the Timers that can be experimented with.
 *
 * @param timer The number of the timer to be initialized (0-2).
 * @param mode The mode to initialize the specified timer in.
 * @param comp Only used in CTC mode. The value that the
 * timer counts to before it triggers an interrupt and resets.
 *
 * @todo Create a function that initializes the desired timer in a given mode and set the compare value
 * (as appropriate).
 */
void initTimer(int timer, int mode, unsigned int comp){
	//Disable interrupts while when we set up the timer.
	cli();

	switch(timer){

	//8 bit timer
	case 0:
		//initialize timer count to 0
		TCNT0 = 0;
		//Enable Timer Overflow Interrupt
		TIMSK0 |= (1<<TOIE0);
		//Enable Timer Interrupt Flag
		TIFR0 |= (1<<TOV0);

		//set timer to lowest freq (~18000 Hz) = (clkI0/1024)
		//001-No Prescaling, 010-clkIO/8, 011-clkIO/64, 100-clkIO/256, 101-clkIO/1024
		TCCR0B |= (1<<CS02)|(1<<CS00);

		//set to CTC if mode = 1, default is normal
		if(mode == 1){
			TCCR0A |= (1<<WGM01);	//set to CTC
			OCR0A = comp;			//set comparison reg
			TIMSK0 |= (1<<OCIE0A);	//Enable Timer interrupts for CTC Mode
			TIFR0 |= (1<<OCF0A);	//Clear Timer compare match flag
		}

		break;

		//16 bit timer w/PWM
	case 1:
		//initialize timer count to 0
		TCNT1 = 0;
		//Enable Timer Overflow Interrupt
		TIMSK1 |= (1<<TOIE1);
		//Enable Timer Interrupt Flag
		TIFR1 |= (1<<TOV1);

		//set timer to lowest freq (~18000 Hz) = (clkI0/1024)
		//001-No Prescaling, 010-clkIO/8, 011-clkIO/64, 100-clkIO/256, 101-clkIO/1024
		TCCR1B |= (1<<CS12)|(1<<CS10);

		//set to CTC if mode = 1, default is normal
		//set to CTC if mode = 1, default is normal
		if(mode == 1){
			TCCR1A |= (1<<WGM12);	//set to CTC
			OCR1A = comp;			//set comparison reg
			TIMSK1 |= (1<<OCIE1A);	//Enable Timer interrupts for CTC Mode
			TIFR1 |= (1<<OCF1A);	//Clear Timer compare match flag
		}

		break;
	case 2:
		//Initialize timer to 0
		TCNT2 = 0;
		//Enable Timer Overflow Interrupt
		TIMSK2 |= (1<<TOIE2);
		//Enable Timer Interrupt Flag
		TIFR2 |= (1<<TOV2);

		//set to CTC if mode = 1, default is normal
		if(mode == 1){
			TCCR2A |= (1<<WGM21);	//set to CTC
			OCR2A = comp;			//set comparison reg
			TIMSK2 |= (1<<OCIE2A);	//Enable Timer interrupts for CTC Mode
			TIFR2 |= (1<<OCF2A);	//Clear Timer compare match flag
		}

		//set timer to lowest freq (~144000 Hz) = (clkI0/128)
		//001-No Prescaling, 010-clkIO/8, 011-clkIO/32, 100 - clkIO/64, 101 - clkIO/128, 100-clkIO/256, 111-clkIO/1024
		TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);
		break;
	default:
		break;
	}
	//Re-enable Global Interrupts
	sei();
}

/**
 * @brief Only used when the specified timer is in CTC mode. Changes
 * the value of the comparison register to the new specified value.
 *
 * @param timer The timer comparison value to change (0-2).
 * @param comp The value to set the comparison register to.
 *
 * @todo Create a function that will set a new compare value for the given timer.
 */
void setCompValue(unsigned char timer, unsigned short int comp){
	switch(timer){
	case 0:
		OCR0A = comp;	//set comparison reg
		break;
	case 1:
		OCR1A = comp;	//set comparison reg
		break;
	case 2:
		OCR2A = comp;	//set comparison reg
		break;
	}

}
