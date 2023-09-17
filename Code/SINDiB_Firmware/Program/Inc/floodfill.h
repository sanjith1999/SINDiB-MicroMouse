/*
 * floodfill.hpp
 *
 *  Created on: Sep 5, 2023
 *      Author: SAMSUNG
 */

#ifndef INC_FLOODFILL_H_
#define INC_FLOODFILL_H_

#define ROWS 10
#define COLUMNS 10

extern int flood[ROWS][COLUMNS];
extern int backFlood[ROWS][COLUMNS];

extern int startPos;

struct coordinate{
	int x;
	int y;
};

void updateWalls(struct coordinate point, int orient, bool L, bool R, bool F);
void floodFill(struct coordinate p, struct coordinate prev);
char toMove(struct coordinate p, struct coordinate prevPos, int orient);
char toMoveBack(struct coordinate p, struct coordinate prevPos, int orient);
void backtrack();
int orientation(int orient, char turning);
struct coordinate updateCoordinates(struct coordinate coordi, int orient);
void rotateFloodCounterClockwise(void);


#endif /* INC_FLOODFILL_H_ */
