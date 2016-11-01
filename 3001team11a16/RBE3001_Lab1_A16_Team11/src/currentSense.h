/*
 * currentSense.h
 *
 *  Created on: Sep 13, 2016
 *      Author: lparnas
 */

#ifndef SRC_CURRENTSENSE_H_
#define SRC_CURRENTSENSE_H_

//Current sense offset in millivolts
//Page 4 of the Current sense Data sheet
#define CURR_SENSE_OFFSET 2497

//Current Sense Gain
#define CURR_SENSE_GAIN 20

//Resistor in the current sense circuit
//Board pinouts circuit diagram
#define CURR_SENSE_RESISTOR 0.05

/**
 * @brief Calculates the current from the current sensor.
 *
 * @param ADCValue, Takes in ADC values in counts form the respective
 * channel
 */
int calcCurrent(unsigned short ADCVal);


#endif /* SRC_CURRENTSENSE_H_ */
