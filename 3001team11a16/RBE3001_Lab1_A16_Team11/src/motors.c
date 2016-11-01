/*
 * motors.c
 *
 *  @author Lumbini Parnas
 *  @author Evan Bosia
 */



#include "RBELib/RBELib.h"
#include "currentSense.h"
#include "globals.h"
#include "utilities.h"


/**
 * Stops arm motors by setting the DAC voltage values to 0
 */
void stopMotors(){
	setDAC(0,0);
	setDAC(1,0);
	setDAC(2,0);
	setDAC(3,0);
}

/**
 * Moves links to desired angles by setting DAC values based off of PID signals.
 * Takes in angle of lower link (lowerTheta) and angle of upper link (upperTheta).
 * NOW USES ENCODERS :D
 *
 * @param lowerTheta --> int
 * @param upperTheta --> int
 */
void gotoAngles(int lowerTheta, int upperTheta){

	//get actual position values from encoders and convert to tenths of a degree
	enc_up = (int)(-2.03 * encCount(UPPER_ENC));
	enc_low = (int)(.89 * encCount(LOWER_ENC));

	//printf("%d   %d\n\r", enc_up, enc_low);

	//get upper signal from PID
	signed int upper_signal = calcPID('H', upperTheta, enc_up);

	//cap upper signal at max DAC value
	if(upper_signal > 4095){
		upper_signal = 4095;
	}
	if(upper_signal < -4095){
		upper_signal = -4095;
	}

	//drive motors
	if(upper_signal > 0){
		setDAC(0,0);
		setDAC(1,upper_signal);
	}else if(upper_signal < 0){
		setDAC(0,-upper_signal);
		setDAC(1,0);
	}else{
		setDAC(0,0);
		setDAC(1,0);
	}

	//get lower signal from PID
	signed int lower_signal = calcPID('L', lowerTheta, enc_low);

	//cap lower signal at max DAC value
	if(lower_signal > 4095){
		lower_signal = 4095;
	}
	if(lower_signal < -4095){
		lower_signal = -4095;
	}

	//drive motors
	if(lower_signal > 0){
		setDAC(3,0);
		setDAC(2,lower_signal);
	}else if(lower_signal < 0){
		setDAC(3,-lower_signal);
		setDAC(2,0);
	}else{
		setDAC(2,0);
		setDAC(3,0);
	}
}

/**
 * @brief Drive the end effector of the arm to a desired X and Y position in the workspace.
 *
 * @param x The desired x position for the end effector.
 * @param y The desired y position for the end effector.
 *
 * @todo Use kinematic equations to move the end effector to the desired position.
 */
void gotoXY(int x, int y);

/**
 * @brief Drive a link (upper or lower) in a desired direction.
 *
 * @param link Which link to control.
 * @param dir Which way to drive the link.
 *
 * @todo Create a way to drive either link in any direction.
 */
void driveLink(int link, int dir);

/**
 * @brief Drive the arm to a "home" position using the potentiometers.  This
 * should be called before using the encoders and just goes to a default position.
 * Once this has been called once, you can initialize/clear the encoders.
 *
 * @todo Drive the arm to a known position using the potentiometers.
 */
void homePos(){
	//	printf("Below 900 --> %d\n\r", potAngle(getADC(2)));
	int up = 0;
	int low = 0;

	int up_array[20];
	int low_array[20];

	stopMotors();

	//get current position of arm using potentiometers
	//reads twenty values from potentiometers to eliminate noise
	for(int i = 0; i < 20; i++){
		up_array[i] = potAngle(getADC(2));
		low_array[i] = potAngle(getADC(3));
		_delay_ms(100);
	}

	//sort values in ascending order to take median
	int temp;
	for(int i=0; i < 19; i++) {
		for(int j=i+1; j < 20; j++) {
			if(up_array[j] < up_array[i]) {
				// swap elements
				temp = up_array[i];
				up_array[i] = up_array[j];
				up_array[j] = temp;
			}
			if(low_array[j] < low_array[i]) {
				// swap elements
				temp = low_array[i];
				low_array[i] = low_array[j];
				low_array[j] = temp;
			}
		}
	}

	//set upper and lower angle (-10 accounts for systemic error)
	up = up_array[9] - 10;
	low = low_array[9];

	//set target upper and lower angle for PID using encoders relative to arbitrary start position
	upper_angle = -(up - 900);
	lower_angle = -low;

	//enable PID control
	enablePID = 1;

	//wait for arm to be in correct position
	wait_for_angles(4);

	//reset encoders encoders
	resetEncCount(UPPER_ENC);
	resetEncCount(LOWER_ENC);

	//set target angles to 0 (now known as absolute)
	upper_angle = 0;
	lower_angle = 0;
}


