//#include "sysModes.h"
//
//void InitMouse()
//{
//}
//
//int idle()
//{
//	while (1)
//		if (buttonPress)
//		{
//			buttonPress = false;
//			break;
//		}
//	return 1;
//}
//
//int speedAdjust()
//{
//	while (1)
//
//	{
//		if (rightIrBlink())
//		{
//			st_speed += 0.01;
//			st_speed += 0.01;
//		}
//
//		if (buttonPress)
//		{
//			buttonPress = false;
//			return 8;
//		}
//		HAL_Delay(1000);
//	}
//}
//
//int startPosChange()
//{
//	while (1)
//	{
//
//		if (irBlink())
//			if (startPos == 3)
//				startPos = 0;
//			else
//				startPos += 1;
//
//		if (buttonPress)
//		{
//			buttonPress = false;
//			return 0;
//		}
//		HAL_Delay(1000);
//	}
//}
