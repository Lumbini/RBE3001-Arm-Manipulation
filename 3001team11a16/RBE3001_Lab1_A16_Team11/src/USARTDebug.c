/*
 * USART.c
 *
 *@author Evan Bosia
 *@author Lumbini Parnas
 */
#include "RBELib/RBELib.h" //RBELib

#define F_CLK 18432000

//Initializes USART communication
void debugUSARTInit(unsigned long baudrate){
	//Check baudrate range
	if(baudrate > 115200 || baudrate < 2400){
		baudrate = 115200;
	}

	UBRR1 = (F_CLK /(16* baudrate)) - 1;

	//Enables USART transmission and receiving
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);

	UCSR1C = 0x06;//(1<<USBS1)|(3<<UCSZ10);
}


//Transmits a character
void putCharDebug(char byteToSend){
	while(!(UCSR1A & (0x20)));
	UDR1 = byteToSend;
}


//Receives a character
unsigned char getCharDebug(void) {
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}


