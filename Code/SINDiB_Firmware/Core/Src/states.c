#include "states.h"

// Define constants for speed limits
#define MIN_SPEED 0
#define MAX_SPEED 100
#define SPEED_INCREMENT 5
#define SPEED_DECREMENT 5

static int speed = 50; // Initial speed value

void SearchRun() {
	static uint8_t searchState = 0; // Initial state is Search Idle

	switch (searchState) {
	case 0: // Search Idle
		// Wait until a signal comes from the IR sensor
		if (IRSignalDetected()) {
			searchState = 1; // Transition to Search Forward
		}
		break;

	case 1: // Search Forward
		// Navigate to the center of the maze from the start cell
		NavigateToCenter();
		searchState = 2;
		break;

	case 2: // Search Backward
		// Navigate back to the start cell from the center cell
		NavigateBackToStart();
		searchState = 0; // Transition back to Search Idle
		break;
	}
}

void FastRun() {
	static uint8_t fastState = 0; // Initial state is fast Idle

	switch (searchState) {
	case 0: // Search Idle
		// Wait until a signal comes from the IR sensor
		if (IRSignalDetected()) {
			searchState = 1; // Transition to Search Forward
		}
		break;

	case 1: // Navigate maze
		// Navigate to the center of the maze from the start cell and come back to start cell
		FastNavigateMaze();
		searchState = 0; // Transition back to fast Idle
		break;
	}
}


void AdjustSpeed() {

    if (leftIRSignalDetected()) {
        // Decrease speed, but ensure it doesn't go below the minimum speed
        speed = (speed - SPEED_DECREMENT > MIN_SPEED) ? (speed - SPEED_DECREMENT) : MIN_SPEED;
    }

    if (rightIRSignalDetected()) {
        // Increase speed, but ensure it doesn't exceed the maximum speed
        speed = (speed + SPEED_INCREMENT < MAX_SPEED) ? (speed + SPEED_INCREMENT) : MAX_SPEED;
    }

}

