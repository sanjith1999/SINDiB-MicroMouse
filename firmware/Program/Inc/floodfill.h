/*
 * floodfill.hpp
 *
 *  Created on: Sep 22, 2023
 *      Author: SAMSUNG
 */

#ifndef INC_FLOODFILL_H_
#define INC_FLOODFILL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include <stdbool.h>



#define ROWS 14
#define COLUMNS 14

extern int flood[ROWS][COLUMNS];
extern int backFlood[ROWS][COLUMNS];
extern int cells[ROWS][COLUMNS];


struct coordinate{
	int y;
	int x;
};

struct surroundCoor {
	struct coordinate N;
	struct coordinate S;
	struct coordinate W;
	struct coordinate E;
};




void updateWalls(struct coordinate point, int orient, bool L, bool R, bool F);
void floodFill(struct coordinate p, struct coordinate prev);
char toMove(struct coordinate p, struct coordinate prevPos, int orient);
char toMoveBack(struct coordinate p, struct coordinate prevPos, int orient);
void backtrack();
int orientation(int orient, char turning);
struct coordinate updateCoordinates(struct coordinate coordi, int orient);
void forwardtrack(struct coordinate dumXY,struct coordinate dumXY_prev, int dumOrient);

#ifdef __cplusplus
}
#endif

#endif /* INC_FLOODFILL_H_ */
