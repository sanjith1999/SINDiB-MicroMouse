#include "main.h"
#include "motor.h"
#include "read_sensors.h"
#include "floodfill.hpp"
#include "cppmain.h"

static coordinate XY; // Declare a coordinate struct
static coordinate XY_prev; // Declare a coordinate struct

static int orient = 0;


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

	XY.x = 0;
	XY.y = 0;

	XY_prev.x = 0;
	XY_prev.y = 0;

	while (1) {

		getSensorReadings();
		updateWalls(XY, orient, L, R, F);

		if (flood[XY.x][XY.y] >= 1) //NotInCenter
				{
			floodFill(XY, XY_prev);
			char direction = toMove(XY, XY_prev, orient);

			if (direction == 'L') {
				straightCountsPID(50);
				(68);
				orient = orientation(orient, direction);
				straightCountsPID(50);
			} else if (direction == 'R') {
				straightCountsPID(50);
				turnGyroLR(-90);
				orient = orientation(orient, direction);
				straightCountsPID(50);
			} else if (direction == 'B') {
				turnGyroLR(90);
				orient = orientation(orient, direction);
				turnGyroLR(90);
				orient = orientation(orient, direction);
				straightCountsPID(100);
			} else if (direction == 'F') {
				straightCountsPID(100);
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
				straightCountsPID(50);
				turnGyroLR(-90);
				orient = orientation(orient, direction);
				straightCountsPID(50);
			} else if (direction == 'R') {
				straightCountsPID(50);
				turnGyroLR(-90);
				orient = orientation(orient, direction);
				straightCountsPID(50);
			} else if (direction == 'B') {
				turnGyroLR(90);
				orient = orientation(orient, direction);
				turnGyroLR(90);
				orient = orientation(orient, direction);
				straightCountsPID(100);
			} else if (direction == 'F') {
				straightCountsPID(100);
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

