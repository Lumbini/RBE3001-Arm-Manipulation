/*
 * PID.c
 *
 *  Created on: Sep 11, 2016
 *  @author Lumbini Parnas
 *  @author Evan Bosia
 */



#include "RBELib/RBELib.h"
#include "globals.h"
#include <stdio.h>

long previous_error_low = 0;	//global previous error for the lower link
long previous_error_high = 0;	//global previous error for the upper link


pidConst pidConsts;

/**
 * @brief Sets the Kp, Ki, and Kd values for 1 link.
 * @details to set the values, use the following style
 * @code pidConst.Kp = 1.3; @endcode
 * @param link The link you want to set the values for (H or L).
 * @param Kp Proportional value.
 * @param Ki Integral value.
 * @param Kd Derivative value.
 *
 * @todo Create a function to the the PID constants for a given link.
 */
void setConst(char link, float Kp, float Ki, float Kd){

	//Sets PID constants for top link
	if(link == 'H'){
		pidConsts.Kp_H = Kp;
		pidConsts.Ki_H = Ki;
		pidConsts.Kd_H = Kd;
	}
	//Sets PID constants for low link
	else if(link == 'L'){
		pidConsts.Kp_L = Kp;
		pidConsts.Ki_L = Ki;
		pidConsts.Kd_L = Kd;
	}
}

/**
 * Takes in which link ('H' or 'L'), set point, and actual position
 * Calculates the PID value.
 *
 * @param  link --> char
 * @param setPoint --> int
 * @param actPos --> int
 *
 * @return pid_signal --> signed int
 *
 */
signed int calcPID(char link, int setPoint, int actPos){

	//Stores the error value
	int pid_error = setPoint - actPos;

	//Stores the output signal of the PID function
	int pid_signal = 0;



	//Generate PID signal based off of link
	if(link == 'L'){
		integral_error_low += 0.01 * pid_error;
		pid_signal = pidConsts.Kp_L * pid_error + pidConsts.Ki_L * integral_error_low + pidConsts.Kd_L * (pid_error - previous_error_low);
		previous_error_low = pid_error;
	}else if(link == 'H'){
		integral_error_high += 0.01 * pid_error;
		pid_signal = (pidConsts.Kp_H * pid_error) + (pidConsts.Ki_H * integral_error_high) + (pidConsts.Kd_H * (pid_error - previous_error_high));
		previous_error_high = pid_error;
	}


	//Set previous error to current error


	//Return signal
	return pid_signal;
}
