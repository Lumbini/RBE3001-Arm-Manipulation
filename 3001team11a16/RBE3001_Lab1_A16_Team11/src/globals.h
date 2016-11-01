/*
 * globals.h
 *
 *  Created on: Sep 29, 2016
 *      Author: Evan
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

//*************************************************************************************************************
//Servo Channels
#define BELT_PIN 7
#define GRIPPER_PIN 6


//*************************************************************************************************************
//ADC Channels
//@TODO Find the pin numbers
#define UPPER_POT_ADC 2
#define LOWER_POT_ADC 3
#define UPPER_CURR_SENSE 0
#define LOWER_CURR_SENSE 1
#define IR1_ADC 4
#define IR2_ADC 5

//*************************************************************************************************************
//Encoder Channels
#define UPPER_ENC 0
#define LOWER_ENC 1

//*************************************************************************************************************
//Thresholds
//@TODO Find these thresholds through experiments
#define HEAVY_CURRENT
#define LIGHT_CURRENT
#define EMPTY_IR 220
#define CLOSEST_IR 550
#define FURTHEST_IR 300

//*************************************************************************************************************
//Other Variables
#define ADC_low 0
#define ADC_high 1023
#define DAC_low 0
#define DAC_high 4095

volatile unsigned int timer0;
volatile unsigned int timer2;
int blockXPos;
int blockYPos;
int enc_up;
int enc_low;

volatile int upper_angle;
volatile int lower_angle;


float integral_error_low;
float integral_error_high;

char enablePID;

void init_globals();


#endif /* SRC_GLOBALS_H_ */
