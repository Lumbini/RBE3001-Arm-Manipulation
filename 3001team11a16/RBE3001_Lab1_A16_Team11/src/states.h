/*
 * states.h
 *
 *  Created on: Oct 7, 2016
 *      Author: Lumbini
 */

#ifndef SRC_STATES_H_
#define SRC_STATES_H_

void initializeSTATE();
void calibrateSTATE();
void startBeltSTATE();
void detectBlockSTATE();
void waitTriggerSTATE();
void moveToXYSTATE();
void waitToPickUpSTATE();
void pickUpSTATE();
void findWeightSTATE();
void sortHeavySTATE();
void sortLightSTATE();

#endif /* SRC_STATES_H_ */
