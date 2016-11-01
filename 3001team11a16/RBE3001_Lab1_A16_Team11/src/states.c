//*************************************************************************************************************//
/*
 * states.c
 *
 *@author Evan Bosia
 *@author Lumbini Parnas
 */
//*************************************************************************************************************//
// This file contains the process run in the state machine

#include "RBELib/RBELib.h" //RBELib
#include "globals.h"
#include "configState.h"
#include "currentSense.h"
#include "utilities.h"

//Function for INITIALIZE enum state
void initializeSTATE(){
	enablePID = 0;

	integral_error_low = 0;
	integral_error_high = 0;

	//Home position
	homePos();
}

//Function for CALIBRATE_SENSORS enum state
void calibrateSTATE(){
	integral_error_low = 0;
	integral_error_high = 0;

	//Set PID constants to normal values
	setConst('H', 20, 1, 75);
	setConst('L', 30, 1, 50);

	//Move arm away from home position to clear the belt
	upper_angle = 0;
	lower_angle = 300;
	_delay_ms(1000);

	//Move arm to block position
	upper_angle = -700;
	lower_angle = 500;

	openGripper();

}
//Function for START_BELT enum state
void startBeltSTATE(){
	//Start the conveyer belt
	startBelt(180);

	//Open Gripper
	openGripper();
}
//Function for DETECT_BLOCK enum state
void detectBlockSTATE(){
	volatile unsigned int xDist = 0;
	volatile unsigned int xArray[] = {0,0,0,0,0};

	//Update xDist with current distance reading
	xDist = xDistIR(IRDist(IR1_ADC));

	//Set Y position of tool tip to be above the block
	blockYPos = 30;

	//if the block is detected...
	if (xDist < 280){
		//run 5 samples from the IR (includes initial sample)
		for(int i = 0; i < 5; i++){
			xArray[i] = xDistIR(IRDist(IR1_ADC));
			_delay_ms(100);
		}

		int temp;
		// the following two loops sort the array x in ascending order
		for(int i=0; i<4; i++) {
			for(int j=i+1; j<5; j++) {
				if(xArray[j] < xArray[i]) {
					// swap elements
					temp = xArray[i];
					xArray[i] = xArray[j];
					xArray[j] = temp;
				}
			}
		}

		//average xDist to get the x position of the block (addition of 12 to to solve systemic error)
		xDist = xArray[1] + 12;
		blockXPos = xDist;

		//printf("%d\n\r", blockXPos);

		//Send X and Y Position to MATLAB to calculate inverse Kinematics
		sendArmData('A');

		//Change state to waiting for trigger
		currentState = WAIT_TRIGGER;
	}
}

//Function for WAIT_TRIGGER enum state
void waitTriggerSTATE(){
	int trigger;

	//Reads IR2
	trigger = IRDist(IR2_ADC);

	//Set PID constants to high Ki to ensure position accuracy
	setConst('H', 30, 10, 200);
	setConst('L', 50, 10, 200);

	//If the block is detected...
	if(trigger > 170){

		//Set arm to move to the angles read in from MATLAB
		sendArmData('G');
		currentState = MOVE_TO_XY;
	}
}

//Function for MOVE_TO_XY enum state
void moveToXYSTATE(){

	//Reset integral error
	integral_error_low = 0;
	integral_error_high = 0;

	//Set Y position of tool tip to be at block level
	blockYPos = -15;

	//Send values to MATLAB
	sendArmData('A');

	//Wait to pickup
	_delay_ms(1800);

	//Set arm to move to the angles read in from MATLAB (now to pickup block)
	sendArmData('G');

	//Wait to close gripper
	_delay_ms(200);
	closeGripper();

	//Wait to make sure gripper is closed before moving
	_delay_ms(300);

	//Set arm angles to pickup block
	upper_angle = -450;
	lower_angle = 450;

}

//Function for WAIT_TO_PICKUP enum state
void waitToPickUpSTATE(){
	//NOT USED everything in MOVE_TO_XY
}

//Function for PICK_UP enum state
void pickUpSTATE(){
	//NOT USED everything in MOVE_TO_XY
}

//Function for FIND_WEIGHT enum state
void findWeightSTATE(){
	int temp;
	int samples = 0;
	volatile signed int current_array[100];

	//Wait until arm is within 3 degrees of upper and lower joint angles
	wait_for_angles(30);

	//Disable PID
	enablePID = 0;

	//Stop Motors from any latent PID signals
	stopMotors();
	_delay_ms(500);

	//Set upper link to a constant voltage for current sense
	setDAC(0,0);
	setDAC(1,1000);

	//Set lower link to a small voltage to avoid sagging
	setDAC(2, 100);
	setDAC(3, 0);

	//Take 50 samples of the current sense circuit to filter noise
	for(samples = 0; samples < 50; samples++){
		_delay_ms(20);
		current_array[samples] = calcCurrent(getADC(UPPER_CURR_SENSE));
	}

	//Stop motors
	stopMotors();

	//Sort the array in ascending order
	for(int i=0; i < 49; i++) {
		for(int j=i+1; j < 50; j++) {
			if(current_array[j] < current_array[i]) {
				// swap elements
				temp = current_array[i];
				current_array[i] = current_array[j];
				current_array[j] = temp;
			}
		}
	}

	//Decides if block is light or heavy based off of current sense median
	if(current_array[25] < -540){
		currentState = SORT_HEAVY;
	}else{
		currentState = SORT_LIGHT;
	}

	//Renable PID
	enablePID = 1;
}

//Function for SORT_HEAVY enum state
void sortHeavySTATE(){
	//Move to Heavy
	//Open gripper
	//Change state back to INITIALIZE
	upper_angle = 0;
	lower_angle = 0;

	//Wait for the angles to be within 1 degrees of the upper and lower set angles
	wait_for_angles(10);

	//Release the block
	openGripper();
	_delay_ms(2000);
}


//Function for SORT_LIGHT enum state
void sortLightSTATE(){
	//Move to Light
	//Open gripper
	//Change state back to INITIALIZATIION

	//Set X and Y values to put block back on conveyor
	blockXPos = 240;
	blockYPos = 20;

	//Send to MATLAB for inverse kinematics
	sendArmData('A');


	//Move arm to clear conveyor
	upper_angle = -450;
	lower_angle = 600;

	//Wait for arm angles to be within 10 degrees of set point
	wait_for_angles(100);

	//Move arm to conveyor position
	sendArmData('G');

	_delay_ms(1000);
	//stop motors
	stopMotors();

	_delay_ms(100);
	//open gripper to release the block
	openGripper();
	_delay_ms(50);

}


