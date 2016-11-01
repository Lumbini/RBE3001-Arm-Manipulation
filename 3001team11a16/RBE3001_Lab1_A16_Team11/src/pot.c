/*
 * pot.c
 *
 *  Created on: Sep 8, 2016
 *  @author Evan Bosia
 */

/**
 * Calculate pot angle in tenths of a degree
 *
 * @param pot --> int
 * @return angle (tenths of a degree) --> int
 */
int potAngle(int pot){
	int angle = 2.4 * (pot - 270);
	return angle;
}

/**
 * Calculate pot value in volts
 *
 * @param pot --> int
 * @return voltage (mV) --> int
 */
int potVolts(int pot){
	int volt = (pot*4.89);
	return volt;
}

