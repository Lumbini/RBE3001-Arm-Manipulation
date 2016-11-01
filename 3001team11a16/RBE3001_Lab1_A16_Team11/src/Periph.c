/*
 * Periph.c
 *
 *  Created on: Sep 22, 2016
 *      Author: lparnas
 */

#include "RBELib/RBElib.h"

/**
 * @brief Find the acceleration in the given axis (X, Y, Z).
 * @param  axis The axis that you want to get the measurement of.
 * @return gVal Value of  acceleration.
 *
 * @todo Create a function that is able to find the acceleration of a given axis.
 */
signed int getAccel(int axis){
	//Working int for reading and shifting data
	unsigned int in = 0;

	// Chip select pin to active-low
	PORTDbits._P7 = 0;
	PORTDbits._P7 = 1;
	PORTDbits._P7 = 0;

	// Transceives the first byte with leading Zeros and then Start bit, mode bit, Don't care bit.
	spiTransceive(0b00000110);

	//Shifts  axis into the first two bits and sends zero bits for receiving
	in = spiTransceive((axis << 6));

	//Shifts the byte that was just read
	in = (in & 0x0F) << 8;

	//sends zeros and receives the rest of the data
	in += spiTransceive(0x00);

	//Chip select Pin to Inactive-High
	PORTDbits._P7 = 1;

	//returns the data from the ADC/Accelerometer
	return (in);
}

/**
 * @brief Read an IR sensor and calculate the distance of the block.
 * @param  chan The port that the IR sensor is on.
 * @return value The distance the block is from the sensor.
 *
 * @todo Make a function that is able to get the ADC value of the IR sensor.
 */
int IRDist(int chan){
	int i = 0;
	//disable and re-enable interrupts during reading to avoid errors
	cli();
	i = getADC(chan);
	sei();
	return i;
}

/**
 * @brief Initialize the encoders with the desired settings.
 * @param chan Channel to initialize.
 *
 * @todo Make a function that can setup both encoder chips on the board.
 */
void encInit(int chan){

	//Quadrature Mode
	char MDR0 = 0b00000001;

	//
	char IR0, IR1;

	//Direction of encoder 0
	//Port C Pin 5
	ENCODER_SS_0_ddr = OUTPUT;

	//Direction of encoder 1
	//Port C Pin 5
	ENCODER_SS_1_ddr = OUTPUT;

	switch(chan){
	case 0:
		//Port C Pin 5
		ENCODER_SS_0 = LOW;



		//B7,B6 = WR Register
		//B5,B4,B3 = Select MDR0 mode
		//B2, B1, B0 = Don't Care bits
		IR0 = 0b10001000;

		//Send set up data to the encoder
		spiTransceive(IR0);
		spiTransceive(MDR0);

		//Turn off encoder
		ENCODER_SS_0 = HIGH;

		break;
	case 1:
		//Port C Pin 4
		ENCODER_SS_1 = LOW;

		//B7,B6 = WR Register
		//B5,B4,B3 = Select MDR0 mode
		//B2, B1, B0 = Don't Care bits
		IR1 = 0b10001000;

		//Send set up data to the encoder
		spiTransceive(IR1);
		spiTransceive(MDR0);

		//Turn off encoder
		ENCODER_SS_1 = HIGH;
		break;
	}
}

/**
 * @brief Reset the current count of the encoder ticks.
 * @param chan The channel to clear.
 *
 * @todo Clear the encoder count (set to 0).
 */
void resetEncCount(int chan){
	char IRReg;
	switch(chan){
	case 0:
		ENCODER_SS_0 = LOW;
		//B5, B4, B3 = 100 Select CNTR
		//B7, B6 = 00 Clear CNTR
		IRReg = 0b00100000;
		spiTransceive(IRReg);
		ENCODER_SS_0 = HIGH;
		break;
	case 1:
		ENCODER_SS_1 = LOW;
		//B5, B4, B3 = 100 Select CNTR
		//B7, B6 = 00 Clear CNTR
		IRReg = 0b00100000;
		spiTransceive(IRReg);
		ENCODER_SS_1 = HIGH;
		break;
	}
}

/**
 * @brief Finds the current count of one of the encoders.
 * @param  chan Channel that the encoder is on that you would like to read.
 * @return count The current count of the encoder.
 *
 * @todo Find the current encoder ticks on a given channel.
 */
signed long encCount(int chan){
	char IRReg;
	signed long enc_count = 0;
	switch(chan){
	case 0:
		ENCODER_SS_0 = LOW;
		//B5, B4, B3 = 100 Select CNTR
		//B7, B6 = 01
		//Set up to Read the Counter
		IRReg = 0b01100000;

		//Send dont care bits to receive data back
		char a0, b0, c0, d0;

		//Send the Instruction register
		spiTransceive(IRReg);
		a0 = spiTransceive(0x00);
		b0 = spiTransceive(0x00);
		c0 = spiTransceive(0x00);
		d0 = spiTransceive(0x00);

		//Parse the received data into a 32 bit long
		enc_count =  (a0 << 24) | (b0 << 16) | (c0<<8) | (d0);

		//Deactivate Encoder 0
		ENCODER_SS_0 = HIGH;

		return enc_count;
		break;
	case 1:
		ENCODER_SS_1 = LOW;
		//B5, B4, B3 = 100 Select CNTR
		//B7, B6 = 00 Clear CNTR
		IRReg = 0b01100000;

		//Send dont care bits to receive data back
		unsigned char a1, b1, c1, d1;

		//Send the Instruction register
		spiTransceive(IRReg);
		a1 = spiTransceive(0x00);
		b1 = spiTransceive(0x00);
		c1 = spiTransceive(0x00);
		d1 = spiTransceive(0x00);

		//Parse the received data into a 32 bit long
		enc_count = (a1 << 24) + (b1 << 16) + (c1<<8) + (d1);

		//Deactivate Encoder 1
		ENCODER_SS_1 = HIGH;
		return enc_count;
		break;
	}
	return -1;
}
