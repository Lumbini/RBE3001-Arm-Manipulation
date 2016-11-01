/*
 * configState.h
 *
 *  Created on: Sep 29, 2016
 *      Author: Lumbini
 */

#ifndef SRC_CONFIGSTATE_H_
#define SRC_CONFIGSTATE_H_

//Create enumerated states for final project stages
typedef enum{
	INITIALIZE,
	CALIBRATE_SENSORS,
	START_BELT,
	DETECT_BLOCK,
	WAIT_TRIGGER,
	MOVE_TO_XY,
	WAIT_TO_PICKUP,
	PICK_UP,
	FIND_WEIGHT,
	SORT_HEAVY,
	SORT_LIGHT
}STATE;

volatile STATE currentState;

void stateFunction();

#endif /* SRC_CONFIGSTATE_H_ */
