/*
 * configState.c
 *
 * @author Lumbini Parnas
 */

#include "RBELib/RBELib.h" //RBELib
#include "globals.h"	//Include main
#include "configState.h"
#include "currentSense.h"
#include "utilities.h"
#include "states.h"


void stateFunction(){

	switch(currentState){

	//Initialize Arm - Home Position
	case INITIALIZE:
		//Send current State to MATLAB
		putCharDebug('I');

		initializeSTATE();

		//Change state to Calibrate
		currentState = CALIBRATE_SENSORS;
		break;

		//Calibrate Sensor
	case CALIBRATE_SENSORS:
		//Send current State to MATLAB
		putCharDebug('C');

		calibrateSTATE();

		//Change state to START_BELT
		currentState = START_BELT;

		//Calibrate IR Sensors???
		break;
	case START_BELT:
		//Send current State to MATLAB
		putCharDebug('B');

		startBeltSTATE();

		//Change state to Detect Block
		currentState = DETECT_BLOCK;
		break;

	case DETECT_BLOCK:
		//Send current State to MATLAB
		putCharDebug('D');

		detectBlockSTATE();
		break;

	case WAIT_TRIGGER:
		//Send current State to MATLAB
		putCharDebug('T');

		waitTriggerSTATE();
		break;

	case MOVE_TO_XY:
		//Send current State to MATLAB
		putCharDebug('M');

		moveToXYSTATE();

		//CHange State
		currentState = PICK_UP;

		break;

	case PICK_UP:
		//Send current State to MATLAB
		putCharDebug('Q');
		//Move to correct Z value
		//Close Gripper
		//State Change to FIND_WEIGHT
		currentState = FIND_WEIGHT;
		break;

	case FIND_WEIGHT:
		//Send current State to MATLAB
		putCharDebug('W');

		findWeightSTATE();

		break;

		//Put in Heavy Shelf
	case SORT_HEAVY:
		//Move to Heavy
		//Open gripper
		//Change state back to INITIALIZE
		//Send current State to MATLAB
		putCharDebug('H');

		sortHeavySTATE();

		currentState = CALIBRATE_SENSORS;
		break;

		//Put in Light Shelf
	case SORT_LIGHT:
		//Move to Light
		//Open gripper
		//Change state back to INITIALIZATIION

		//Send current State to MATLAB
		putCharDebug('L');

		sortLightSTATE();

		currentState = CALIBRATE_SENSORS;
		break;
	}
}
