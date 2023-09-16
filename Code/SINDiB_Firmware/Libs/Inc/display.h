#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdio.h>
#include <string.h>

#include "ssd1306.h"

void clearScreen();
void printString_font_6x8(char* str, int x, int y);
void printInt_font_6x8(int INT, int x, int y);
void printFloat_font_6x8(float FLOAT, int x, int y);



#endif /* INC_DISPLAY_H_ */
