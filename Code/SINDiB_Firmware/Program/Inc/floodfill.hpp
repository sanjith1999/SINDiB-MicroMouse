/*
 * floodfill.hpp
 *
 *  Created on: Sep 5, 2023
 *      Author: SAMSUNG
 */

#ifndef INC_FLOODFILL_HPP_
#define INC_FLOODFILL_HPP_

#define ROWS 16
#define COLUMNS 16

extern int flood[ROWS][COLUMNS];
extern int backFlood[ROWS][COLUMNS];

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
coordinate updateCoordinates(struct coordinate coordi, int orient);


#endif /* INC_FLOODFILL_HPP_ */
