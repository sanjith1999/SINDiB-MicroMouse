/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
 */
#include "cppmain.h"

u32 i;
u32 DELAY_MID = 1;
bool buttonPress = false;
int mouseState = 0;
int runState = 0;
static coordinate XY;
static coordinate XY_prev;

int orient = 1;
char direction;
bool starting = false;
float edgeToCenter = 12.5;
float centerToEdgeSides = 3;
float centerToEdgeForward = 3.5;
float centerToEdgeBack = 2;
float Angle180 = 180;
float centerToEdge;

void mouseRun();

int cppmain(void)
{
	initialization_block();
	HAL_Delay(1000);
	disp_state = DEFAULT;

	if (orient == 1)
	{
		XY.x = 1;
		XY.y = 0;
		cells[0][0] = 10;
	}
	else
	{
		XY.x = 0;
		XY.y = 1;
		cells[0][0] = 9;
	}

	XY_prev.y = 0;
	XY_prev.x = 0;
	bool run1 = true, run2 = false;
	while (1)
	{
		// if (run1)
		// if (finishMove(FRONT_ALIGN, 0))
		// 	{
		// 		run2 = true, run1 = false;
		// 		STOP_ROBOT;
		// 		HAL_Delay(2000);
		// 	}
		// if (run2)
		// 	if (finishMove(POINT_TURN, 90))
		// 	{
		// 		run1 = true, run2 = false;
		// 		STOP_ROBOT;
		// 		HAL_Delay(2000);
		// 	}

		mouseRun();
		//		getSensorReadings();
		i++;
		HAL_Delay(1);
	}
}

int initialization_block(void)
{
	ALL_LED_ON;
	TIM1_START; ////////////////// CRUCIAL PART DON"T OFFFFFFFFFFFFFFFF ///////////////////////////
	TIM6_IT_START;

	motorInit();
	encoderInit();
	gyroInit();
	displayInit();
	buzzerInit();

	ALL_LED_OFF;
	HAL_Delay(1000);
	gyroCalibration();
	disp_state = DEFAULT;
	TIM13_IT_START;
	// TIM14_IT_START;

	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim14)
		;
	else if (htim == &htim13)
		gyroUpdate(),
			readSensor();
	else if (htim == &htim6)
		displayUpdate();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == TB1_Pin)
	{
		buttonPress = true;
	}
	else
	{
		__NOP();
	}
}

void mouseRun()
{
	switch (mouseState)
	{

	case 0: // Idle
		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 1;
			buttonPress = false;
		}
		break;

	case 1: // search Idle
		if (irBlink())
		{
			HAL_Delay(1000);
			mouseState = 2;
		}

		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 4;
			buttonPress = false;
			runState = 0;
		}
		break;

	case 2: // searchForward

		switch (runState)
		{

		case 0: // starting
			if (finishMove(STRAIGHT_RUN, 7.0))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				runState = 1;
			}
			break;

		case 1: // decision
			getSensorReadings();
			updateWalls(XY, orient, L, R, F);

			if (flood[XY.y][XY.x] >= 1) // NotInCenter
			{
				floodFill(XY, XY_prev);
				direction = toMove(XY, XY_prev, orient);
				runState = 2;
			}
			else
			{ // in center
				LED5_ON;
				backtrack();
				direction = toMoveBack(XY, XY_prev, orient);
				mouseState = 3;
				runState = 2;
			}
			HAL_Delay(DELAY_MID);
			break;

		case 2: // move center
			if(!F){
				align_select = true;
			}
			
			if (finishMove(STRAIGHT_RUN, edgeToCenter))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				runState = 5;
			}
			break;

		case 5: // align
			if (F)
			{
				if (finishMove(FRONT_ALIGN, 16))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					runState = 3;
				}
			}
			else
			{
				runState = 3;
			}

			break;

		case 3: // turning
			if (direction == 'L')
			{
				if (finishMove(POINT_TURN, 90))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'R')
			{
				if (finishMove(POINT_TURN, -90))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'B')
			{
				if (finishMove(POINT_TURN, Angle180))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'F')
			{
				HAL_Delay(DELAY_MID);
				runState = 4;
			}
			break;

		case 4: // move to edge
			if (direction == 'L' || direction == 'R')
			{
				centerToEdge = centerToEdgeSides;
			}
			else if (direction == 'B')
			{
				centerToEdge = centerToEdgeBack;
			}
			else if (direction == 'F')
			{
				centerToEdge = centerToEdgeForward;
			}
			if (finishMove(STRAIGHT_RUN, centerToEdge))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				runState = 1;
				XY_prev = XY;
				XY = updateCoordinates(XY, orient);
			}
			break;
		}

		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 4;
			buttonPress = false;
		}
		break;

	case 3: // search backward

		switch (runState)
		{

		case 0: // finishing
			if (finishMove(STRAIGHT_RUN, edgeToCenter))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				mouseState = 0;
			}
			break;

		case 1: // decision
			getSensorReadings();
			direction = toMoveBack(XY, XY_prev, orient);

			if (backFlood[XY.y][XY.x] == 0)
			{
				runState = 0;
			}
			else
			{
				runState = 2;
			}
			break;

		case 2: // move center
			if(!F){
				align_select = true;
			}
			if (finishMove(STRAIGHT_RUN, edgeToCenter))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				runState = 3;
			}
			break;

		case 5:
			if (F)
			{
				if (finishMove(FRONT_ALIGN, 16))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					runState = 3;
				}
			}
			else
			{
				runState = 3;
			}
			break;

		case 3: // turning
			if (direction == 'L')
			{
				if (finishMove(POINT_TURN, 90))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'R')
			{
				if (finishMove(POINT_TURN, -90))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'B')
			{
				if (finishMove(POINT_TURN, Angle180))
				{
					STOP_ROBOT;
					HAL_Delay(DELAY_MID);
					resetEncoder();
					orient = orientation(orient, direction);
					runState = 4;
				}
			}
			else if (direction == 'F')
			{
				HAL_Delay(DELAY_MID);
				runState = 4;
			}
			break;

		case 4: // move edge
			if (direction == 'L' || direction == 'R')
			{
				centerToEdge = centerToEdgeSides;
			}
			else if (direction == 'B')
			{
				centerToEdge = centerToEdgeBack;
			}
			else if (direction == 'F')
			{
				centerToEdge = centerToEdgeForward;
			}
			if (finishMove(STRAIGHT_RUN, centerToEdge))
			{
				STOP_ROBOT;
				HAL_Delay(DELAY_MID);
				runState = 1;
				XY_prev = XY;
				XY = updateCoordinates(XY, orient);
			}
			break;
		}
		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 4;
			buttonPress = false;
		}

		break;

	case 4: // fast idle

		if (irBlink())
		{
			HAL_Delay(1000);
			mouseState = 5;
		}

		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 7;

			buttonPress = false;
		}

		break;

	case 5:
		//			mouseState = fastForward();

		if (buttonPress)
		{

			HAL_Delay(1000);
			mouseState = 7;
			buttonPress = false;
		}

		break;

	case 6: // fastBackward

		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 7;
			buttonPress = false;
		}
		break;

	case 7:
		//			mouseState = speedAdjust();

		if (buttonPress)
		{

			HAL_Delay(1000);
			mouseState = 8;

			buttonPress = false;
		}

		break;

	case 8: // set initial //////////////////////////////////////////////////////////// ASK FROM ISHRATH //////////////////////////////////////////////////////////

		if (irBlink())
		{
			// if (state == 1)
			// {
			// 	orient = 0;
			// }
			// else
			// {
			// 	orient = 1;
			// }

			// if (orient == 1)
			// {
			// 	XY.x = 1;
			// 	XY.y = 0;
			// 	cells[0][0] = 10;
			// }
			// else
			// {
			// 	XY.x = 0;
			// 	XY.y = 1;
			// 	cells[0][0] = 9;
			// }

			// XY_prev.y = 0;
			// XY_prev.x = 0;
		}

		if (buttonPress)
		{
			HAL_Delay(1000);
			mouseState = 0;
			buttonPress = false;
		}

		break;

	default:
		break;
	}
}
