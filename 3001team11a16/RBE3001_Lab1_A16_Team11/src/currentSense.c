/*
 * currentSense.c
 *
 * @author Lumbini Parnas
 */
#include "RBELib/RBELib.h" //RBELib


/**
 * @brief Calculates the current from the current sensor.
 *
 * @param ADCValue --> unsigned short
 * @return current --> int
 */

int calcCurrent(unsigned short ADCVal){
	//Convert ADCVal to millivolts using the ratio
	//5000/1023 = 4.8875855
	//Subtract the Current Sensor Offset to shift and allow bidirectional sensing
	float milliVolts = (ADCVal*4.8876) - 2688;

	//multiplied by gains (in this case gains are 1/20 and 20)
	int current = milliVolts;
	return current;
}
