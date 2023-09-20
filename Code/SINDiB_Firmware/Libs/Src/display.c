#include "display.h"

DISP_State disp_state;

void displayInit(void){
	ssd1306_Init();
	disp_state = INIT;
	displayUpdate();
}

void clearScreen()
{
	ssd1306_Fill(Black);
}

void writeString(char *str, FONT_Size font_size)
{
	switch (font_size)
	{
	case SMALL:
		ssd1306_WriteString(str, Font_6x8, White);
		break;
	case MEDIUM:
		ssd1306_WriteString(str, Font_7x10, White);
		break;
	case LARGE:
		ssd1306_WriteString(str, Font_11x18, White);
		break;
	case HUGE:
		ssd1306_WriteString(str, Font_16x24, White);
		break;
	}
}

void putString(char *str, int x, int y, FONT_Size font_size)
{
	ssd1306_SetCursor(x, y);
	writeString(str, font_size);
}

void putChar(char chr, int x, int y, FONT_Size font_size)
{
	char str[2];
	// Copy the character into the string
	str[0] = chr;
	// Null-terminate the string
	str[1] = '\0';
	ssd1306_SetCursor(x, y);
	writeString(str, font_size);
}

void putInt(int INT, int x, int y, FONT_Size font_size)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%d", INT);
	ssd1306_SetCursor(x, y);
	writeString(buff, font_size);
}

void putFloat(float FLOAT, int x, int y, FONT_Size font_size)
{
	char buff[64];
	snprintf(buff, sizeof(buff), "%.2f", FLOAT); // Change %.2f to adjust precision
	ssd1306_SetCursor(x, y);
	writeString(buff, font_size);
}


void displayUpdate(void)
{
	clearScreen();
	switch (disp_state)
	{
	// INITIALIZATION BLOCK: AUDI CAR EXPECTED
	case (INIT):
		for (int delta = 0; delta < 5; delta++)
			ssd1306_DrawCircle(16 * delta + 35, 15, 10, White);
		break;

	// DEFAULT SCREEN --> BATTERY PERCENTAGE, STATE OF THE ROBOT
	case (DEFAULT):
		// DISPLAYING BATTERY VOLTAGE
		putString("BAT:",74,2,SMALL);
		putFloat(voltage,104 , 2, SMALL);

		putString("TURN:",2,16,MEDIUM);
		// putString(turn,44,16,MEDIUM);
		break;

	case (GYRO_CALIB):
		putString("NOISE: ",2,2,SMALL);
		putFloat(noise,64, 2, SMALL);
 
		putString("OFFSET: ",2,11,SMALL);
		putInt(offset,64,11,SMALL);

		putString("ANGLE: ",2,22,SMALL);
		putFloat(angle_z,64,22,SMALL);
		break;

	case (SENSOR_READ):

		putString("LF:",2,2,SMALL);
		putInt(LFSensor,26,2, SMALL);

		putString("RF:",76,2,SMALL);
		putInt(RFSensor,100,2, SMALL);

		putString("DL:",2,13,SMALL);
		putInt(DLSensor,26,13, SMALL);

		putString("DR:",76,13,SMALL);
		putInt(DRSensor,100,13, SMALL);
		
		putString("ANGLE:",22,24,SMALL);
		putFloat(angle_z,70,22, SMALL);
		break;

	case (LOW_BAT):
		putString("BAT LOW...!",2,7,LARGE);
		break;

	case (SUCESS_MSG):
		putString("HURRAYYYY!!!",2,2,LARGE);
		putString("SINDiB na kokka",2,22,SMALL);
		break;
	}
	ssd1306_UpdateScreen();
	LED6_TOG;
}