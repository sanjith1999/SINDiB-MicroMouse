/*
 MAIN FILE CONTAINING ALL OUR CODES
 TEAM: SINDiB
 AUTHOR: BIYON
 */
#include "cppmain.h"

u32 i;
bool buttonPress = false;
int mouseState = 0;
int runState = 0;
static coordinate XY;
static coordinate XY_prev;

int orient = 0;
char direction;
bool starting = false;

int cppmain(void)
{
	initialization_block();
	HAL_Delay(1000);
	disp_state = DEFAULT;
	LED3_ON;
	LED4_ON;
	LED5_ON;

	while (1)
	{

		switch (mouseState)
		{

		case 0: // Idle
			if (buttonPress)
			{
				HAL_Delay(1000);
				mouseState = 1;
				buttonPress = false;
				LED3_ON;
				LED4_OFF;
				LED5_OFF;
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
				if (finishMove( STRAIGHT_RUN, 3.0)) {
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
					backtrack();
					direction = toMoveBack(XY, XY_prev, orient);
					mouseState = 3;
					runState = 2;
				}
				break;

			case 2: // move center
				//				if (forward(7.0)) {
				//					runState = 3;
				//				}
				break;

			case 3: // turning
				if (direction == 'L')
				{
					//					if (pintTurnLeft()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'R')
				{
					//					if (pintTurnLeft()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'B')
				{
					//					if (pintTurn180()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'F')
				{
					//					if (Stop()) {
					//						runState = 4;
					//					}
				}
				break;

			case 4: // move to edge
				//				if (forward(1.0)) {
				//					runState = 1;
				//					XY_prev = XY;
				//					XY = updateCoordinates(XY, orient);
				//				}
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

			case 0: // starting
				//				if (forward(3.0)) {
				//					runState = 1;
				//				}
				break;

			case 1: // decision
				direction = toMoveBack(XY, XY_prev, orient);

				if (backFlood[XY.y][XY.x] == 0)
				{
					mouseState = 0;
				}
				else
				{
					backtrack();
					mouseState = 3;
					runState = 1;
				}
				break;

			case 2: // move center
				//				if (forward(7.0)) {
				//					runState = 3;
				//				}
				break;

			case 3: // turning
				if (direction == 'L')
				{
					//					if (pintTurnLeft()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'R')
				{
					//					if (pintTurnLeft()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'B')
				{
					//					if (pintTurn180()) {
					//						orient = orientation(orient, direction);
					//						runState = 4;
					//					}
				}
				else if (direction == 'F')
				{
					//					if (Stop()) {
					//						runState = 4;
					//					}
				}
				break;

			case 4: // move edge
				//				if (forward(3.0)) {
				//					runState = 1;
				//				}
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
				LED3_OFF;
				LED4_ON;
				LED5_OFF;
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
				LED5_OFF;
				LED4_OFF;
				LED5_ON;
				buttonPress = false;
			}

			break;

		case 8:
			//			mouseState = setInitial();

			if (buttonPress)
			{

				HAL_Delay(1000);
				mouseState = 0;
				LED5_OFF;
				LED4_OFF;
				LED3_ON;
				LED4_ON;
				LED5_ON;
				buttonPress = false;
			}

			break;

		default:
			break;
		}
		i++;
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
	// buzzerInit();

	ALL_LED_OFF;
	HAL_Delay(1000);
	gyroCalibration();
	disp_state = DEFAULT;
	TIM13_IT_START;

	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim14)
		readSensor();
	else if (htim == &htim13)
		gyroUpdate(), readSensor();
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