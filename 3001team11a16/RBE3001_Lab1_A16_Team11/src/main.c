
/*
 * main.c
 *
 *@author Evan Bosia
 *@author Lumbini Parnas
 */
//*************************************************************************************************************
//Libraries
#include "RBELib/RBELib.h"	//RBELib
#include "timeStamp.h"		//Include source file with time stamp functions
#include "currentSense.h"
#include "buttons.h"
#include "configState.h"
#include "globals.h"
#include "utilities.h"
#include "states.h"


//*************************************************************************************************************
//Function Prototypes
void initAll();

//*************************************************************************************************************
//Main Function
int main(void){
	//Initialize all Libraries
	initAll();

	//Initialize the state to INITIALIZE
	currentState = INITIALIZE;

	while(1){
		//run stateFunction at 10 Hz
		if(timer2 > 9){
			stateFunction();
			timer2 = 0;
		}
	}
}

void initAll(){
	initRBELib();	//Initialize RBELib
	init_globals();	//Initialize globals

	//Initialize USART to allow for serial communication (default baud is 115200)
	debugUSARTInit(DEFAULT_BAUD);

	initSPI();	//Initialize SPI

	//Initialize Encoders:
	encInit(UPPER_ENC);		//Upper
	encInit(LOWER_ENC);		//Lower

	resetEncCount(UPPER_ENC);
	resetEncCount(LOWER_ENC);

	//Initialize Timers
	//Initialize timer to 1000Hz (Timer0, CTC Mode, 17 comparator)
	//initTimer(0,1,17);

	//Initialize timer2 to 800Hz (Timer2, CTC Mode, 179 comparator)
	initTimer(2,1,179);

	setConst('H', 20, 1, 75);
	setConst('L', 30, 1, 50);

	//Initialize ADCs
	initADC(0);
}

//TIMER2 ISR
//Calls PID every 100Hz
ISR(TIMER2_COMPA_vect){

	//If PID is enabled, run PID
	if(enablePID == 1) gotoAngles(lower_angle, upper_angle);

	//Send arm angles to MATLAB at 10Hz
	if(timer0 > 10){
		sendArmData('P');
		timer0 = 0;
	}
	timer0++;
	timer2++;
}


