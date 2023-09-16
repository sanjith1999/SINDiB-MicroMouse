#include "display.h"

void clearScreen(){
	ssd1306_Fill(Black);
}

void printString_font_6x8(char* str, int x, int y){
	ssd1306_SetCursor(x, y);

	ssd1306_WriteString(str, Font_6x8, White);
	ssd1306_UpdateScreen();
}

void printChr_font_6x8(char chr, int x, int y){
	char str[2];
	// Copy the character into the string
	str[0] = chr;
	// Null-terminate the string
	str[1] = '\0';

	ssd1306_SetCursor(x, y);

	ssd1306_WriteString(str, Font_6x8, White);
	ssd1306_UpdateScreen();
}

void printInt_font_6x8(int INT, int x, int y){
	char buff[64];
	snprintf(buff, sizeof(buff), "%d", INT);

	ssd1306_SetCursor(x, y);

	ssd1306_WriteString(buff, Font_6x8, White);
	ssd1306_UpdateScreen();
}

void printFloat_font_6x8(float FLOAT, int x, int y) {
    char buff[64];
    snprintf(buff, sizeof(buff), "~%.2f", FLOAT); // Change %.2f to adjust precision

    ssd1306_SetCursor(x, y);

    ssd1306_WriteString(buff, Font_6x8, White);
    ssd1306_UpdateScreen();
}

