/*
 * DAC.c
 *
 *  Created on: Sep 10, 2016
 *      Author: lparnas
 */

#include <RBELib/RBELib.h>	//RBELib


/**
 * @brief Set the DAC to the given value on the chosen channel.
 * @param  DACn The channel that you want to set.
 * @param SPIVal The value you want to set it to.
 *
 * @todo Make the function that is able to set the DAC to a given value
 * from 0 - 4095.
 */
void setDAC(int DACn, int SPIVal){
	//DAC is active low so write signal low
	DAC_SS = 0;	//Activate Chip Select
	DAC_SS = 1;	//Deactivate Chip Select
	DAC_SS = 0;	//Activate Chip Select

	//Command Codes Page 20 of DAC datasheet
	//Write to and update DAC register n: 0b0011
	spiTransceive(0b00110000|(uint8_t)DACn);

	//Transmitting data
	//SPIVal is an int - 16 bit data
	spiTransceive((uint8_t) (SPIVal >> 4)); 	// Send first 12 bits
	spiTransceive((uint8_t)(0xFF & (uint8_t)(SPIVal << 4)));	// Send the next 4 bits

	DAC_SS = 1;	//Deactivate chip select
}
