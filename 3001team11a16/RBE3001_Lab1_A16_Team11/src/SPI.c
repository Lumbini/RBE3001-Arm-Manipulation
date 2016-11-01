/*
 * SPI.c
 *
 *  @author Lumbini Parnas
 */

#include <avr/io.h>
#include <RBELib/reg_structs.h>
#include <RBELib/RBELib.h>	//RBELib


/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI(){
	// Set MOSI as OUTPUT
	SPI_MOSI_DDR = OUTPUT;
	//Set SCK as OUTPUT
	SPI_SCK_DDR = OUTPUT;
	//MISO for AVR (SPI Master Mode)
	SPI_MISO_DDR = INPUT;

	//Initialize SPI Slave Device
	//Set MISO as OUTPUT
	DDRBbits._P4 = OUTPUT;


	//SET AVR Slave Select HIGH because it is active low
	PORTBbits._P4 = HIGH;

	DDRDbits._P4 = OUTPUT;

	DDRBbits._P5 = OUTPUT;

	DDRDbits._P7 = OUTPUT;

	DAC_SS = 1;
	ENCODER_SS_0 = 1;
	ENCODER_SS_1 = 1;
	PORTDbits._P7 = 1;


	PRR = 0;
	//Enable SPI, Set register SPE to 1
	//Set SPI Mode to Master, set MSTR reg to 1
	SPCR = (1<<SPE)|(1<<MSTR);

	//Set Prescaler to 128
	//SCK Freq = Fosc/128 = 144000Hz
	//SPCR |= (1<<SPR0);
	SPCR |= (1<<SPR1);
	//SPSR &= ~(1<<SPI2X);
}

/**
 * @brief Send and receive a byte out of the MOSI line.
 *
 * Please note that even if you do not want to receive any data back
 * from a SPI device, the SPI standard requires you still receive something
 * back even if it is junk data.
 *
 * @param data The byte to send down the SPI bus.
 * @return value The byte shifted in during transmit
 *
 * @todo Make a function that will send a byte of data through the SPI
 * and return whatever was sent back.
 */
unsigned char spiTransceive(BYTE data){
	//Load Data into buffer
	SPDR = data;
	//Wait till transmission is complete
	//When a serial transfer is complete the SPIF flag is set.
	while(!(SPSR & (1<<SPIF)));

	//Return Received data
	return(SPDR);
}
