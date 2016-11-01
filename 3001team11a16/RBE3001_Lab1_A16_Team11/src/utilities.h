/*
 * utilities.h
 *
 *  Created on: Oct 3, 2016
 *      Author: lparnas
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

void startBelt(int speed);
void openGripper();
void closeGripper();
int xDistIR(int irADC);
int avgArray(int arrElements[]);
void sendArmData(char sendMode);
void wait_for_angles(int buffer);


#endif /* SRC_UTILITIES_H_ */
