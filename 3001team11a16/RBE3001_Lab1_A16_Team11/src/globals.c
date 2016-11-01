/*
 * globals.c
 *
 *  Created on: Sep 29, 2016
 *      Author: Evan
 */

volatile unsigned int timer0;	//incrementing variable in timer2 --> used for sending arm data at 10Hz
volatile unsigned int timer2;	//incrementing variable in timer2 --> used for calling state machine at 10Hz

volatile int upper_angle;	//upper link angle
volatile int lower_angle;	//lower link angle

int blockXPos;	//x position of block
int blockYPos;	//y position used to control height of arm when picking up block
int enc_low;	//lower encoder value
int enc_up;		//upper encoder value

float integral_error_low;	//integral error for the lower link
float integral_error_high;	//integral error for the upper link

char enablePID;	//0 disables PID, 1 enables PID

void init_globals(){
	timer0 = 0;
	timer2 = 10;	//allows for a first time pass through stateFunction (timer2 is initialized in homePos)
	blockXPos = 0;
	blockYPos = 0;
	enc_up = 0;
	enc_low = 0;
	enablePID = 0;
	integral_error_low = 0.0;
	integral_error_high = 0.0;
}
