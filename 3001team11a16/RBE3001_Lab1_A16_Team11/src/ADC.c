/**
 * ADC.c
 *
 * @author Evan Bosia
 * @author Lumbini Parnas
 */

#include "RBELib/RBELib.h"

/**
 * Takes in a channel for the ADC.
 * Enables the ADC, setting it to the passed in channel, and sets up the clock
 *
 * @param channel --> int
 */
void initADC(int channel){

	//Sets ADC to inputed channel
	changeADC(channel);

	//Enables ADC
	//Sets prescaler to 128, making the clock frequency 144000 Hz
	ADCSRA = 0b10000111;

}

/**
 * Disables ADC functionality and clears any saved values (globals).
 *
 * @param channel --> int
 */
void clearADC(int channel){
	ADCSRA &= (1<<ADEN);
	ADC = 0;
}

/**
 * Gets the value read by the ADC.
 *
 * @param channel --> int
 *
 * @return adcVal --> unsigned short
 */
volatile unsigned short getADC(int channel){
	//Changes ADC channel to inputed channel
	changeADC(channel);

	//Starts conversion
	ADCSRA |= (1<<ADSC);

	//Waits for conversion
	while(ADCSRA & (1<<ADSC));

	//Returns combination of high and low ADC registers
	return ADCL | (ADCH << 8);
}

/**
 * Changes the channel of ADC sampling.
 *
 * @param channel --> int
 */
void changeADC(int channel){
	//Converts input channel to 8bit data type
	char ch = (char)(channel);

	//Clears all data except last 3 bits (0 - 7 range)
	//These bits are the only ones needed for changing the ADC channel
	ch &= 0x07;

	//Sets ADC channel
	//Sets ADC output to 8 bits of low, last 2 bits of high
	//			ADCH = ------XX
	//			ADCL = XXXXXXXX
	ADMUX = (0b01000111 & 0xF8)|ch;
}


