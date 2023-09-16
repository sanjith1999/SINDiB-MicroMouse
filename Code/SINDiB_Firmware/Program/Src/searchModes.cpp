#include <floodfill.h>
#include "main.h"
#include "motor.h"
#include "read_sensors.h"
#include "cppmain.h"
#include "searchModes.h"

static coordinate XY; // Declare a coordinate struct
static coordinate XY_prev; // Declare a coordinate struct

static int orient = 2;


//     orients :
//         0- North
//         1- East
//         2- South
//         3- West

int searchIdle() {

	while (1) {
		if (irBlink()) {
			return 2;
		}

		if (buttonPress) {
			buttonPress = false;
			return 4;
		}
	}
}

int searchForward() {


	for (int i = 0; i <= startPos; i++) {
		rotateFloodCounterClockwise();
	    }

	XY.x = 1;
	XY.y = 0;

	XY_prev.x = 0;
	XY_prev.y = 0;

	while (1) {


		clearScreen();
		printInt_font_6x8(LFSensor, 80, 10);
		printInt_font_6x8(RFSensor, 2, 10);
		printInt_font_6x8(DLSensor, 80, 24);
		printInt_font_6x8(DRSensor, 2, 24);
		getSensorReadings();

		HAL_Delay(4000);

		updateWalls(XY, orient, L, R, F);

		if (flood[XY.x][XY.y] >= 1) //NotInCenter
				{
			floodFill(XY, XY_prev);
			char direction = toMove(XY, XY_prev, orient);

			clearScreen();
			printChr_font_6x8(direction, 40, 16);

			HAL_Delay(4000);

			if (direction == 'L') {
				cellTurnLeft();
				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				cellTurnRight();
				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				cellTurnBack();
				orient = orientation(orient, direction);
			} else if (direction == 'F') {
				moveStraight(16);
			}

			XY_prev = XY;
			XY = updateCoordinates(XY, orient);

		} else {
			return 3;
		}

		if (buttonPress) {
			buttonPress = false;
			return 4;
		}
	}

	return 3;
}

int searchBackward() {
	backtrack();

	while (1) {
		if (backFlood[XY.x][XY.y] >= 1) //NotInStart
				{

			char direction = toMoveBack(XY, XY_prev, orient);

			if (direction == 'L') {
				cellTurnLeft();
				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				cellTurnRight();
				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				cellTurnBack();
				orient = orientation(orient, direction);
			} else if (direction == 'F') {
				moveStraight(16);
			}

			XY_prev = XY;
			XY = updateCoordinates(XY, orient);

		} else {
			return 4;
		}

		if (buttonPress) {
			buttonPress = false;
			return 4;
		}
	}
	return 7;
}

