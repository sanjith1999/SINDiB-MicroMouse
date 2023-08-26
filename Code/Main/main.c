#include "searchModes.h"
#include "fastModes.h"
#include "sysModes.h"


int mouseState = 0;


int main(void)
{

	InitMouse();
		
	while(1)
	{	
		switch (mouseState) 
		{
			
			case 0:
				std::cout << "Idle state.\n";
				mouseState = idle();
				break;

			case 1:
				std::cout << "search idle state.\n";
				mouseState = searchIdle();
				break;

			case 2:
				std::cout << "search forward state.\n";
				mouseState = searchForward();
				break;

			case 3:
				std::cout << "search backward state.\n";
				mouseState = searchBackward();
				break;

			case 4:
				std::cout << "fast idle state.\n";
				mouseState = fastIdle();
				break;

			case 5:
				std::cout << "fast forward state.\n";
				mouseState = fastForward();
				break;

			case 6:
				std::cout << "fast backward state.\n";
				mouseState = fastBackward();
				break;

			case 7:
				std::cout << "speed adjust state.\n";
				mouseState = speedAdjust();
				break;

			default:
				std::cout << "error : Unknown state.\n";
				break;
		}

    

	}

	return 0;
}