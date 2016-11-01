/*
 * timeStamp.c
 *
 * @author Lumbini Parnas
 */
#include "RBELib/RBELib.h"	//RBELib
#include "timeStamp.h"

//Sets the global time to 0
void initGlobalTime(void){
	milliSeconds = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
}

//Changes the time variables based off of if the previous overflowed
void initKeepTime(void){
	if (milliSeconds >= 1000){
		seconds ++;
		milliSeconds = 0;
	}
	if (seconds >= 60){
		minutes++;
		seconds = 0;
	}
	if(minutes >= 60){
		hours ++;
		minutes = 0;
	}
}

//Prints the times stamp comma delineated
void printTimeStamp(void){
	printf("%d,%d,%d,%d", hours,minutes,seconds,milliSeconds);
}
