#include "main.h"
#include "motor.h"
#include "sensors.h"
#include "floodfill.hpp"

coordinate XY; // Declare a coordinate struct
coordinate XY_prev; // Declare a coordinate struct


static int orient = 0;

//     orients :
//         0- North
//         1- East
//         2- South
//         3- West

int searchIdle() {

	return 2;

	// while(1)
	// {
	//     if(irBlink())
	//     {
	//         return 2;
	//     }
	//     if(buttonPress())
	//     {
	//         return 4;
	//     }

	// }
}

int searchForward() {
//	startPos(); // move to

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
				turnLeft(68);
//				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				turnRight(68);
//				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				turnLeft(68);
//				orient = orientation(orient, direction);
				turnLeft(68);
//				orient = orientation(orient, direction);
			}

			straightCountsPID(100);
			XY_prev = XY;
//			XY = updateCoordinates(XY, orient);


		} else {
			return 3;
		}
	}

	return 3;
}

int searchBackward() {
	backtrack();

	while (1) {
		if (backFlood[XY.x][XY.y] >= 1) //NotInStart
				{
			char direction = toMove(XY, XY_prev, orient);

			if (direction == 'L') {
				turnLeft(68);
//				orient = orientation(orient, direction);
			} else if (direction == 'R') {
				turnRight(68);
//				orient = orientation(orient, direction);
			} else if (direction == 'B') {
				turnLeft(68);
//				orient = orientation(orient, direction);
				turnLeft(68);
//				orient = orientation(orient, direction);
			}

			straightCountsPID(100);
			XY_prev = XY;
			// XY = updateCoordinates(XY, orient);

		} else {
			return 4;
		}
	}
	return 7;
}

