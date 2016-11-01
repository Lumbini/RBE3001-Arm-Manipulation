/*
 * utilities.c
 *
 * @author Lumbini Parnas
 * @author Evan Bosia
 */

#include "RBELib/RBELib.h" //RBELib
#include "globals.h"	//Include main
#include "configState.h"
#include "currentSense.h"


//Start conveyer belt at the required speed
void startBelt(int speed){
	setServo(BELT_PIN, speed);
}

//Open the Gripper
void openGripper(){
	setServo(GRIPPER_PIN, 0);
}

//Close the Gripper
void closeGripper(){
	setServo(GRIPPER_PIN, 180);
}

//Returns distance value from IR sensor
int xDistIR(int irADC){
	//260 is the distance from the base of the arm to the center of the block in the farthest position
	int xFromOrig = 260 - ((irADC - 335) * 0.315);
	return xFromOrig;
}

int avgArray(int arrElements[]){
	int i;
	int sum = 0;
	int avg;
	for (i = 0; i < sizeof(arrElements) +1; i++){
		sum+=arrElements[i];
	}
	avg = sum/sizeof(arrElements);
	return avg;
}
void sendArmData(char sendMode){
	int xVal = blockXPos;
	int yVal = blockYPos;

	int upPot = 0;
	int lowPot = 0;

	char up_h, up_l, low_h, low_l;

	switch(sendMode){
	//Plot Mode
	case 'P':
		upPot = potAngle(getADC(UPPER_POT_ADC)) - 900;
		lowPot = potAngle(getADC(LOWER_POT_ADC));

		//Send error checking character
		putCharDebug('P');

		//Send upper angle
		putCharDebug((char)(upPot));
		putCharDebug((char)(upPot >> 8));

		//Send upper angle
		putCharDebug((char)(lowPot));
		putCharDebug((char)(lowPot >> 8));

		break;
	//Inverse Kinematics Mode Calculate Angles
	case 'A':
		//Send error checking character
		putCharDebug('A');

		//Send Required X Position
		putCharDebug((char)(xVal));
		putCharDebug((char)(xVal >> 8));

		//Send Required Y Position
		putCharDebug((char)(yVal));
		putCharDebug((char)(yVal >> 8));
		break;
	case 'G':
		putCharDebug('G');
		up_h = getCharDebug();
		up_l = getCharDebug();
		low_h = getCharDebug();
		low_l = getCharDebug();

		upper_angle = (up_h << 8) + up_l;
		lower_angle = (low_h << 8) + low_l;
		break;
	}

	//Send when ready to receive angles and move the motor
}

//Waits for arm angles to be within +/- the buffer value from the set point
void wait_for_angles(int buffer){
	char up_check = 0;	//upper check
	char low_check = 0;	//lower check

	//reset integral error
	integral_error_low = 0;
	integral_error_high = 0;

	//loop until up_chekc and low_check are greater than 10 (meaning the arm has settled)
	while((up_check < 10) || (low_check < 10)){

		//if the upper encoder value is within the upper buffer
		if(((upper_angle - buffer) < enc_up) && (enc_up < (upper_angle + buffer))){
			up_check++;
		}else{
			up_check = 0;
		}

		//if the lower encoder value is within the lower buffer
		if(((lower_angle - buffer) < enc_low) && (enc_low < (lower_angle + buffer))){
			low_check++;
		}else{
			low_check = 0;
		}
		//delay readings by 50ms
		_delay_ms(50);

		//Increase I when arm is close to final angle
		if((upper_angle - enc_up) < 150){
			setConst('H', 20, 20, 500);
		}
		else{
			integral_error_high = 0;
			setConst('H', 10, 0, 50);
		}
		if((lower_angle - enc_low) < 150){
			setConst('L', 20, 20, 500);
		}
		else{
			integral_error_low = 0;
			setConst('L', 10, 0, 50);
		}
	}

	//Set PID constants to normal values
	setConst('H', 20, 1, 75);
	setConst('L', 30, 1, 50);
}

