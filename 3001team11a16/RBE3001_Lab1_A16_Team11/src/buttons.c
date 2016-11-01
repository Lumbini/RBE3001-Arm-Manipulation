/*
 * buttons.c
 *
 *  Created on: Sep 13, 2016
 *      Author: lparnas
 */

#include "RBELib/RBELib.h" //RBELib


/*
 * @brief Initialize the buttons connected to pins C4 to C7
 * as external interrupts
 *
 */

void buttonInit(void){
	//Disable global interrupts
	cli();

	// Configure buttons as inputs
	DDRAbits._P0 = INPUT;
	DDRAbits._P1 = INPUT;
	DDRAbits._P6 = INPUT;
	DDRAbits._P7 = INPUT;

	PORTAbits._P0 = HIGH;
	PORTAbits._P1 = HIGH;
	PORTAbits._P6 = HIGH;
	PORTAbits._P7 = HIGH;

	//Set Pin change external interrupts 31 to 28
//	PCMSK3 |= (1<<PCINT31);
//	PCMSK3 |= (1<<PCINT30);
//	PCMSK3 |= (1<<PCINT29);
//	PCMSK3 |= (1<<PCINT28);

//	PCMSK3 |= 0xF0;
//
//	//Enable Pin change interrupts 31 to 28
//	//PCICR |= (1<<PCIE3);
//	PCICR |= 0x4;
//
//	//CLear Pin change interrupt Flag 31 to 28
//	//PCIFR |= (1<<PCIF3);
//	PCIFR |= 0x4;

	//Enable global Interrupts
	sei();
}
