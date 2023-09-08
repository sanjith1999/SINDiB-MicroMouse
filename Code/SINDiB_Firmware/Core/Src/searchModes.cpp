#include "main.h"

static int x = 0, y = 0;
static int xprev =0, yprev =0;
static int orient=0;


//     orients :
//         0- North
//         1- East
//         2- South
//         3- West



int searchIdle()
{

    return 2;

    // while(1)
    // {
    //     if(irBlink())
    //     {
    //         return 2;
    //     }
    //     if(buttonPress())
    //     {
    //         return 4;
    //     }

    // }

}

int searchForward()
{
    // startPos(); // move to

    // while(1)
    // {
    //     L,R,F = getSensorReadings();
    //     updateWalls();

    //     if(flood[x][y]>=1) //NotInCenter
    //     {
    //         floodFill(x,y,xprev,yprev);
    //         char direction = toMove(x,y,xprev,yprev,orient);

    //         if (direction=='L')
    //         {
    //             searchTurnLeft()
    //         }
    //         elif (direction=='R'):
    //             searchTurnRight()

    //         elif (direction=='B'):
    //             searchTurnBack()

    //         elif (direction=='F'):
    //             searchGoForward()

    //         orient = orientation(orient,direction);

    //     }
    //     else
    //     {
    //         return 3;
    //     }


    //     if(buttonPress)
    //     {
	//			delay(1000);
    //         return 4;
    //     }

    // }

    return 3;

}

int searchBackward()
{
    // backtrack();

    // while(1)
    // {
    //     if(backFlood[x][y]>=1) //NotInStart
    //     {
    //         direction= toMoveBack(x,y,xprev,yprev,orient);

    //         if (direction=='L')
    //         {
    //             searchTurnLeft()
    //         }
    //         elif (direction=='R'):
    //             searchTurnRight()

    //         elif (direction=='B'):
    //             searchTurnBack()

    //         elif (direction=='F'):
    //             searchGoForward()

    //         orient = orientation(orient,direction);

    //     }
    //     else
    //     {
    //         return 4;
    //     }

    //     if(buttonPress())
    //     {
    //         return 4;
    //     }

    // }

    return 7;
}

