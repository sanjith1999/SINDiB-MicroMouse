#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdio.h>
#include <string.h>
#include "typedefs.h"

#include "ssd1306.h"

// CLEARNING SCREEN
void clearScreen();

// WRITING STRING ON SCREEN
void writeString(char *str, FONT_size font_size);

// PUTTING A STRING ON SPECIFIED LOCATION
void putString(char *str, int x, int y, FONT_Size font_size);

// PUTTING A CHARACTOR ON SPECIFIED LOCATION
void putChar(char chr, int x, int y, FONT_Size font_size);

// PUTTING A INT ON SPECIFIED LOCATION
void putInt(int INT, int x, int y, FONT_Size font_size);

// PUTTING A FLOAT ON SPECIFIED LOCATION
void putFloat(float FLOAT, int x, int y, FONT_Size font_size);

// DISPLAY UPDATE
void displayUpdate(DISP_State disp_state)



#endif /* INC_DISPLAY_H_ */
