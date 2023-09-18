#include "display.h"

void clearScreen()
{
	ssd1306_Fill(Black);
}

void writeString(char *str, FONT_size font_size)
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

void displayUpdate(DISP_State disp_state)
{
	switch (disp_state)
	{
	// INITIALIZATION BLOCK: AUDI CAR EXPECTED
	case (INIT):
		for (delta = 0; delta < 5; delta++)
			ssd1306_DrawCircle(20 * delta + 30, 15, 10, White);

		for (delta = 0; delta < 5; delta++)
			ssd1306_FillCircle(23 * delta + 15, 40, 10, White);
		break;

	// DEFAULT SCREEN --> BATTERY PERCENTAGE, STATE OF THE ROBOT
	case (DEFAULT):
		break;
	case (GYRO_CALIB):
		break;
	case (SENSOR_READ):
		break;
	case (LOW_BAT):
		break;
	case (SUCESS_MSG):
		break;
	}
}

int