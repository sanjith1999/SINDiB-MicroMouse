#include "main.h"
#include "motor.h"
#include "floodfill.hpp"

static coordinate XY; // Declare a coordinate struct
static coordinate XY_prev; // Declare a coordinate struct

static int orient = 0;

int fastIdle() {

	while (1) {
		if (irBlink()) {
			return 5;
		}

		if (buttonPress) {
			buttonPress = false;
			return 7;
		}
	}
}

int fastForward() {

	XY.x = 0;
	XY.y = 0;

	XY_prev.x = 0;
	XY_prev.y = 0;

	while (1) {
		if (flood[XY.x][XY.y] >= 1) //NotInCenter
				{
			char direction = toMove(XY, XY_prev, orient);

			if (direction == 'L') {
				turnLeft(68);
				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				turnRight(68);
				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				turnLeft(68);
				orient = orientation(orient, direction);
				turnLeft(68);
				orient = orientation(orient, direction);
			}

			straightCountsPID(100);
			XY_prev = XY;
			XY = updateCoordinates(XY, orient);

		} else {
			return 6;
		}

		if (buttonPress) {
			buttonPress = false;
			return 7;
		}
	}

	return 6;
}

int fastBackward() {

	while (1) {
		if (backFlood[XY.x][XY.y] >= 1) //NotInCenter
				{
			char direction = toMoveBack(XY, XY_prev, orient);

			if (direction == 'L') {
				turnLeft(68);
				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				turnRight(68);
				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				turnLeft(68);
				orient = orientation(orient, direction);
				turnLeft(68);
				orient = orientation(orient, direction);
			}

			straightCountsPID(100);
			XY_prev = XY;
			XY = updateCoordinates(XY, orient);

		} else {
			return 7;
		}

		if (buttonPress) {
			buttonPress = false;
			return 7;
		}

	}

	return 7;
}

