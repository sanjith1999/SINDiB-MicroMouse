#include <floodfill.h>
#include "stm32f4xx_hal.h"
#include <stdbool.h>

int x = 0;
int y = 0;
int orient = 0;
int debug = 0;

int startPos = 0;

//int flood[ROWS][COLUMNS]={
//		{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
//		{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
//		{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
//		{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
//		{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
//		{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
//		{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
//		{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
//		{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
//		{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
//		{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
//		{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
//		{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
//		{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
//		{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
//		{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},
//};
//int cells[ROWS][COLUMNS]={
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//};
//int backFlood[ROWS][COLUMNS]={
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//};

// int flood[ROWS][COLUMNS]={
// 		{6,5,4,3,3,4,5,6,7,8},
// 		{5,4,3,2,2,3,4,5,6,7},
// 		{4,3,2,1,1,2,3,4,5,6},
// 		{3,2,1,0,0,1,2,3,4,5},
// 		{3,2,1,0,0,1,2,3,4,5},
// 		{4,3,2,1,1,2,3,4,5,6},
// 		{5,4,3,2,2,3,4,5,6,7},
// 		{6,5,4,3,3,4,5,6,7,8},
// 		{7,6,5,4,4,5,4,7,8,9},
// 		{8,7,6,5,5,6,5,8,9,10},
//};
//int cells[ROWS][COLUMNS]={
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//};
//int backFlood[ROWS][COLUMNS]={
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,},
//};

int flood[ROWS][COLUMNS] = { { 2, 2, 3, 4, 5 }, { 1, 1, 2, 3, 4 }, { 0, 0, 1, 2,
		3 }, { 0, 0, 1, 2, 3 }, { 1, 1, 2, 3, 4 },

};
int cells[ROWS][COLUMNS] =
		{ { 9, -1, -1, -1, -1, }, { -1, -1, -1, -1, -1, },
				{ -1, -1, -1, -1, -1, }, { -1, -1, -1, -1, -1, }, { -1, -1, -1,
						-1, -1, }, };
int backFlood[ROWS][COLUMNS] = { { -1, -1, -1, -1, -1, },
		{ -1, -1, -1, -1, -1, }, { -1, -1, -1, -1, -1, },
		{ -1, -1, -1, -1, -1, }, { -1, -1, -1, -1, -1, }, };

void rotateFloodCounterClockwise(void) {
	int original[ROWS][COLUMNS];
	// Copy the contents of 'flood' into 'original'
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			original[i][j] = flood[i][j];
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			flood[i][j] = original[j][ROWS - 1 - i];
		}
	}
}

struct surroundCoor {
	struct coordinate N;
	struct coordinate S;
	struct coordinate W;
	struct coordinate E;
};

struct QNode {
	struct coordinate point;
	QNode *next;
	QNode(struct coordinate p) {
		point = p;
		next = NULL;
	}
};

struct Queue {
	QNode *front, *rear;
	Queue() {
		front = rear = NULL;
	}

	bool isempty() {
		if (front == NULL && rear == NULL) {
			return true;
		} else {
			return false;
		}
	}

	void enQueue(struct coordinate point) {

		// Create a new LL node
		QNode *temp = new QNode(point);

		// If queue is empty, then
		// new node is front and rear both
		if (rear == NULL) {
			front = rear = temp;
			return;
		}

		// Add the new node at
		// the end of queue and change rear
		rear->next = temp;
		rear = temp;
	}

	// Function to remove
	// a key from given queue q
	struct coordinate deQueue() {
		// If queue is empty, return NULL.
		if (front == NULL) {
		} else {
			// Store previous front and
			// move front one node ahead
			QNode *temp = front;
			front = front->next;

			// If front becomes NULL, then
			// change rear also as NULL
			if (front == NULL)
				rear = NULL;

			delete (temp);
			return temp->point;
		}
	}
};

// Structure of Node.
//struct Node
//{
//	struct coordinate point;
//	Node *link;
//};
//
//
//bool isempty(struct Node front, struct Node rear)
//{
// if(front == NULL && rear == NULL){
//	 return true;
// }
// else{
//	 return false;
// }
//}
//
////function to enter elements in queue
//void enqueue (struct coordinate p,struct Node front, struct Node rear)
//{
//	Node *ptr = new Node();
//	ptr->point= p;
//	ptr->link = NULL;
//
//	//If inserting the first element/node
//	if( front == NULL )
//	{
//		front = ptr;
//		rear = ptr;
//	}
//	else
//	{
//		rear ->link = ptr;
//		rear = ptr;
//	}
//}
//
////function to delete/remove element from queue
//struct coordinate dequeue(struct Node front, struct Node rear )
//{
//	if( isempty() ){
//	 // cout<<"Queue is empty\n";
//	}
//	else{
//		//only one element/node in queue.
//		if( front == rear)
//		{
//			Node *ptr = front;
//			delete(front);
//			front = rear = NULL;
//			return ptr->point;
//		}
//		else
//		{
//			Node *ptr = front;
//			front = front->link;
//			return ptr->point;
//		}
//	}
//}

/*
 orients :
 0- North
 1- East
 2- South
 3- West
 */

void updateWalls(struct coordinate point, int orient, bool L, bool R, bool F) {
	if ((L && R) && F) {
		if (orient == 0) {
			cells[point.x][point.y] = 13;
		}            //|-|
		else if (orient == 1) {
			cells[point.x][point.y] = 12;
		}            //_-|
		else if (orient == 2) {
			cells[point.x][point.y] = 11;
		}            //|_|
		else if (orient == 3) {
			cells[point.x][point.y] = 14;
		}            //|-_
	} else if ((L && R) && (!F)) {
		if (orient == 0) {
			cells[point.x][point.y] = 9;
		}            //| |
		else if (orient == 1) {
			cells[point.x][point.y] = 10;
		}            //_-
		else if (orient == 2) {
			cells[point.x][point.y] = 9;
		}            //| |
		else if (orient == 3) {
			cells[point.x][point.y] = 10;
		}            //_-
	} else if ((L && F) && (!R)) {
		if (orient == 0) {
			cells[point.x][point.y] = 8;
		}            //|-
		else if (orient == 1) {
			cells[point.x][point.y] = 7;
		}            //-|
		else if (orient == 2) {
			cells[point.x][point.y] = 6;
		}            //_|
		else if (orient == 3) {
			cells[point.x][point.y] = 5;
		}            //|_
	} else if ((R && F) && (!L)) {
		if (orient == 0) {
			cells[point.x][point.y] = 7;
		}            //-|
		else if (orient == 1) {
			cells[point.x][point.y] = 6;
		}            //_|
		else if (orient == 2) {
			cells[point.x][point.y] = 5;
		}            //|_
		else if (orient == 3) {
			cells[point.x][point.y] = 8;
		}            //|-
	} else if (F) {
		if (orient == 0) {
			cells[point.x][point.y] = 2;
		}            //-
		else if (orient == 1) {
			cells[point.x][point.y] = 3;
		}            // |
		else if (orient == 2) {
			cells[point.x][point.y] = 4;
		}            //_
		else if (orient == 3) {
			cells[point.x][point.y] = 1;
		}            //|
	} else if (L) {
		if (orient == 0) {
			cells[point.x][point.y] = 1;
		}            //|
		else if (orient == 1) {
			cells[point.x][point.y] = 2;
		}            //-
		else if (orient == 2) {
			cells[point.x][point.y] = 3;
		}            // |
		else if (orient == 3) {
			cells[point.x][point.y] = 4;
		}            //_
	} else if (R) {
		if (orient == 0) {
			cells[point.x][point.y] = 3;
		}            // |
		else if (orient == 1) {
			cells[point.x][point.y] = 4;
		}            //_
		else if (orient == 2) {
			cells[point.x][point.y] = 3;
		}            //|
		else if (orient == 3) {
			cells[point.x][point.y] = 4;
		}            //-
	} else {
		cells[point.x][point.y] = 0;            //
	}
}

bool isAccessible(struct coordinate p, struct coordinate p1) {
	if (p1.x < 0 || p1.y < 0 || p1.x >=ROWS  || p1.y >= COLUMNS) {
		return false;
	}

	if (p.x == p1.x) {
		if (p.y > p1.y) {
			if (cells[p.x][p.y] == 4 || cells[p.x][p.y] == 5
					|| cells[p.x][p.y] == 6 || cells[p.x][p.y] == 10
					|| cells[p.x][p.y] == 11 || cells[p.x][p.y] == 12
					|| cells[p.x][p.y] == 14) {
				return false;
			}

			else {
				return true;
			}
		} else {
			if (cells[p.x][p.y] == 2 || cells[p.x][p.y] == 7
					|| cells[p.x][p.y] == 8 || cells[p.x][p.y] == 10
					|| cells[p.x][p.y] == 12 || cells[p.x][p.y] == 13
					|| cells[p.x][p.y] == 14) {
				return false;
			}

			else {
				return true;
			}

		}
	} else if (p.y == p1.y) {
		if (p.x > p1.x) {
			if (cells[p.x][p.y] == 1 || cells[p.x][p.y] == 5
					|| cells[p.x][p.y] == 8 || cells[p.x][p.y] == 9
					|| cells[p.x][p.y] == 11 || cells[p.x][p.y] == 13
					|| cells[p.x][p.y] == 14) {
				return false;
			} else {
				return true;
			}
		} else {
			if (cells[p.x][p.y] == 3 || cells[p.x][p.y] == 6
					|| cells[p.x][p.y] == 7 || cells[p.x][p.y] == 9
					|| cells[p.x][p.y] == 11 || cells[p.x][p.y] == 12
					|| cells[p.x][p.y] == 13) {
				return false;
			} else {
				return true;
			}
		}
	} else {
		return false;
	}
}

struct surroundCoor getSurrounds(struct coordinate p) {
	struct surroundCoor surCoor;
	surCoor.N.x = p.x - 1;
	surCoor.N.y = p.y;

	surCoor.S.x = p.x + 1;
	surCoor.S.y = p.y;

	surCoor.W.x = p.x;
	surCoor.W.y = p.y - 1;

	surCoor.E.x = p.x;
	surCoor.E.y = p.y + 1;

	if (surCoor.S.x >= ROWS) {
		surCoor.S.x = -1;
	}
	if (surCoor.E.y >= COLUMNS) {
		surCoor.E.y = -1;
	}

	return surCoor;
}

bool isConsistant(struct coordinate p) {
	struct surroundCoor surr = getSurrounds(p);
	int minVals[4];
	if (surr.N.x >= 0 && surr.N.y >= 0) {
		if (isAccessible(p, surr.N)) {
			minVals[0] = flood[surr.N.x][surr.N.y];
		}
	}
	if (surr.E.x >= 0 && surr.E.y >= 0) {
		if (isAccessible(p, surr.E)) {
			minVals[1] = flood[surr.E.x][surr.E.y];
		}
	}
	if (surr.W.x >= 0 && surr.W.y >= 0) {
		if (isAccessible(p, surr.W)) {
			minVals[2] = flood[surr.W.x][surr.W.y];
		}
	}
	if (surr.S.x >= 0 && surr.S.y >= 0) {
		if (isAccessible(p, surr.S)) {
			minVals[3] = flood[surr.S.x][surr.S.y];
		}
	}
	int val = flood[p.x][p.y];
	int minCount = 0;
	for (int i = 0; i < 4; i++) {
		if (minVals[i] == val - 1 && minVals[i] != -1) {
			minCount++;
		}
	}

	if (minCount > 0 || val == 0) {
		return true;
	} else {
		return false;
	}

}

void makeConsistant(struct coordinate p) {
	struct surroundCoor surr = getSurrounds(p);
	int minVals[4];
	if (surr.N.x >= 0 && surr.N.y >= 0) {
		if (isAccessible(p, surr.N)) {
			minVals[0] = flood[surr.N.x][surr.N.y];
		}
	}
	if (surr.E.x >= 0 && surr.E.y >= 0) {
		if (isAccessible(p, surr.E)) {
			minVals[1] = flood[surr.E.x][surr.E.y];
		}
	}
	if (surr.W.x >= 0 && surr.W.y >= 0) {
		if (isAccessible(p, surr.W)) {
			minVals[2] = flood[surr.W.x][surr.W.y];
		}
	}
	if (surr.S.x >= 0 && surr.S.y >= 0) {
		if (isAccessible(p, surr.S)) {
			minVals[3] = flood[surr.S.x][surr.S.y];
		}
	}
	int minimum = 1000;
	for (int i = 0; i < 4; i++) {
		if (minVals[i] == -1) {
			minVals[i] = 1000;
		}
		if (minVals[i] < minimum) {
			minimum = minVals[i];
		}
	}
	flood[p.x][p.y] = minimum + 1;
}

void floodFill(struct coordinate p, struct coordinate prev) {
	if (!isConsistant(p)) {
		flood[p.x][p.y] = flood[prev.x][prev.y] + 1;
	}

	Queue q;
	q.enQueue(p);

	while (!q.isempty()) {
		struct coordinate crun = q.deQueue();
		if (isConsistant(crun)) {

		} else {
			makeConsistant(crun);
			q.enQueue(crun);
			struct surroundCoor surr = getSurrounds(crun);
			if (surr.N.x >= 0 && surr.N.y >= 0) {
				if (isAccessible(crun, surr.N)) {
					q.enQueue(surr.N);
				}
			}
			if (surr.E.x >= 0 && surr.E.y >= 0) {
				if (isAccessible(crun, surr.E)) {
					q.enQueue(surr.E);
				}
			}
			if (surr.W.x >= 0 && surr.W.y >= 0) {
				if (isAccessible(crun, surr.W)) {
					q.enQueue(surr.W);
				}
			}
			if (surr.S.x >= 0 && surr.S.y >= 0) {
				if (isAccessible(crun, surr.S)) {
					q.enQueue(surr.S);
				}
			}
		}
	}

}

char toMove(struct coordinate p, struct coordinate prevPos, int orient) {
	struct surroundCoor surr = getSurrounds(p);
//	int val = flood[p.x][p.y];
	int minVals[4] = { 1000, 1000, 1000, 1000 };
	int prevDir = 0;
	if (surr.N.x >= 0 && surr.N.y >= 0) {
		if (isAccessible(p, surr.N)) {
			minVals[0] = flood[surr.N.x][surr.N.y];
			if (surr.N.x == prevPos.x && surr.N.y == prevPos.y) {
				prevDir = 0;
			}
		}
	}
	if (surr.E.x >= 0 && surr.E.y >= 0) {
		if (isAccessible(p, surr.E)) {
			minVals[1] = flood[surr.E.x][surr.E.y];
			if (surr.E.x == prevPos.x && surr.E.y == prevPos.y) {
				prevDir = 1;
			}
		}
	}
	if (surr.W.x >= 0 && surr.W.y >= 0) {
		if (isAccessible(p, surr.W)) {
			minVals[2] = flood[surr.W.x][surr.W.y];
			if (surr.W.x == prevPos.x && surr.W.y == prevPos.y) {
				prevDir = 2;
			}
		}
	}
	if (surr.S.x >= 0 && surr.S.y >= 0) {
		if (isAccessible(p, surr.S)) {
			minVals[3] = flood[surr.S.x][surr.S.y];
			if (surr.S.x == prevPos.x && surr.S.y == prevPos.y) {
				prevDir = 3;
			}
		}
	}
	int minimum = 1000;
	int noMovements = 0;
	for (int i = 0; i < 4; i++) {
		if (minVals[i] != 1000) {
			noMovements++;
		}
	}

	int minCell = 0;
	for (int i = 0; i < 4; i++) {
		if (minVals[i] < minimum) {
			if (noMovements == 1) {
				minimum = minVals[i];
				minCell = i;
			} else {
				if (i == prevDir) {

				} else {
					minimum = minVals[i];
					minCell = i;
				}
			}

		}
	}

	if (minCell == orient) {
		return 'F';
	} else if (minCell == orient - 1 || minCell == orient + 3) {
		return 'L';
	} else if (minCell == orient + 1 || minCell == orient - 3) {
		return 'R';
	} else {
		return 'B';
	}

}

char toMoveBack(struct coordinate p, struct coordinate prevPos, int orient) {
	struct surroundCoor surr = getSurrounds(p);
//	int val = backFlood[p.x][p.y];
	int minVals[4] = { 1000, 1000, 1000, 1000 };

	if (surr.N.x >= 0 && surr.N.y >= 0) {
		if (isAccessible(p, surr.N)) {
			minVals[0] = backFlood[surr.N.x][surr.N.y];
		}
	}
	if (surr.E.x >= 0 && surr.E.y >= 0) {
		if (isAccessible(p, surr.E)) {
			minVals[1] = backFlood[surr.E.x][surr.E.y];
		}
	}
	if (surr.W.x >= 0 && surr.W.y >= 0) {
		if (isAccessible(p, surr.W)) {
			minVals[2] = backFlood[surr.W.x][surr.W.y];
		}
	}
	if (surr.S.x >= 0 && surr.S.y >= 0) {
		if (isAccessible(p, surr.S)) {
			minVals[3] = backFlood[surr.S.x][surr.S.y];
		}
	}

	int minimum = 1000;
	int minCell = 0;
	for (int i = 0; i < 4; i++) {
		if (minVals[i] != 1000 && minVals[i] < minimum) {
			minimum = minVals[i];
			minCell = i;
		}
	}

	if (minCell == orient) {
		return 'F';
	} else if (minCell == orient - 1 || minCell == orient + 3) {
		return 'L';
	} else if (minCell == orient + 1 || minCell == orient - 3) {
		return 'R';
	} else {
		return 'B';
	}
}

void backtrack() {
	struct coordinate p;
	p.x = 0;
	p.y = 0;
	int distance = 1;

	backFlood[0][0] = 0;
	Queue q;

	q.enQueue(p);

	while (!q.isempty()) {
		Queue temq;

		int br = 0;

		while (!q.isempty()) {
			p = q.deQueue();

			if (flood[p.x][p.y] == 0) {
				br = 1;
				break;
			}
			struct surroundCoor surr = getSurrounds(p);

			if (surr.N.x >= 0 && surr.N.y >= 0 && cells[surr.N.x][surr.N.y] >= 0
					&& backFlood[surr.N.x][surr.N.y] == -1) {
				if (isAccessible(p, surr.N)) {
					temq.enQueue(surr.N);
					backFlood[surr.N.x][surr.N.y] = distance;
				}
			}
			if (surr.E.x >= 0 && surr.E.y >= 0 && cells[surr.E.x][surr.E.y] >= 0
					&& backFlood[surr.E.x][surr.E.y] == -1) {
				if (isAccessible(p, surr.E)) {
					temq.enQueue(surr.E);
					backFlood[surr.E.x][surr.E.y] = distance;
				}
			}
			if (surr.S.x >= 0 && surr.S.y >= 0 && cells[surr.S.x][surr.S.y] >= 0
					&& backFlood[surr.S.x][surr.S.y] == -1) {
				if (isAccessible(p, surr.S)) {
					temq.enQueue(surr.S);
					backFlood[surr.S.x][surr.S.y] = distance;
				}
			}
			if (surr.W.x >= 0 && surr.W.y >= 0 && cells[surr.W.x][surr.W.y] >= 0
					&& backFlood[surr.W.x][surr.W.y] == -1) {
				if (isAccessible(p, surr.W)) {
					temq.enQueue(surr.W);
					backFlood[surr.W.x][surr.W.y] = distance;
				}
			}

		}

		if (br) {
			break;
		}
		q = temq;
		distance += 1;
	}

}

int orientation(int orient, char turning) {
	if (turning == 'L') {
		orient -= 1;
		if (orient == -1) {
			orient = 3;
		}
	}

	else if (turning == 'R') {
		orient += 1;
		if (orient == 4) {
			orient = 0;
		}
	}

	else if (turning == 'B') {
		if (orient == 0) {
			orient = 2;
		} else if (orient == 1) {
			orient = 3;
		} else if (orient == 2) {
			orient = 0;
		} else if (orient == 3) {
			orient = 1;
		}
	}
	return orient;
}

struct coordinate updateCoordinates(struct coordinate coordi, int orient) {
	if (orient == 0) {
		coordi.x -= 1;
	}
	if (orient == 1) {
		coordi.y += 1;
	}
	if (orient == 2) {
		coordi.x += 1;
	}
	if (orient == 3) {
		coordi.y -= 1;
	}
	return coordi;
}
