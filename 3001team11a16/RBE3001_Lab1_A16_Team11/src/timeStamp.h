/*
 * timeStamp.h
 *
 * @author Lumbini Parnas
 */

#ifndef SRC_TIMESTAMP_H_
#define SRC_TIMESTAMP_H_

//Variables to keep time
volatile unsigned int milliSeconds;
volatile unsigned int seconds;
volatile unsigned int minutes;
volatile unsigned int hours;

void initKeepTime(void);
void printTimeStamp(void);
void initGlobalTime(void);


#endif /* SRC_TIMESTAMP_H_ */
