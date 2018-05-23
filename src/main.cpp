#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

#include <ncurses.h>

#include "color.h"
#include "control.h"
#include "window.h"

//The programs main entry point
int main()
{
	//**********************//
	//* Initialize ncurses *//
	//**********************//

	initscr();												//Initializing ncurses screen
	cbreak();												//Disable buffering of typed characters
	noecho();												//Disable automatic echoing of typed characters
	keypad(stdscr, true);									//Enable capturing of special keys
	curs_set(0);											//Hide the cursor

	//Check if terminal has color support, if not display error the exit the program.
	//TODO: Right now this projects relies on color support. Black and White only support could be added later.
	if (has_colors() == FALSE)
	{
	    endwin();
	    std::cout << "Your terminal does not support color\n";
	    std::exit(1);
	}

	start_color();											//Initializing ncurses colors
	setupColorPairs();										//Setting up the color pairs. Implemented in color.c

	//********************//
	//* DEBUG SETUP CODE *//
	//********************//

	DefaultWindowHost winHost(COLS, LINES, 0, 0, stdscr);

	TunnelWindow testWin1(.2, 1, 0, 0, true, true, false, true);
	testWin1.setDefaultColor(COLOR_PAIR(P_FGW));
	winHost.addWindow(&testWin1);

	TunnelWindow testWin2(.2, .5, 0, .2, true, true, false, true);
	testWin2.setDefaultColor(COLOR_PAIR(P_BGW));
	winHost.addWindow(&testWin2);

	TunnelWindow testWin3(.6, 1, 0, .4, true, true, false, true);
	testWin3.setDefaultColor(COLOR_PAIR(P_BGW));
	winHost.addWindow(&testWin3);

	winHost.resizeWindowHost(COLS, LINES);

	/*testWin1.setBorder();
	testWin2.setBorder();
	testWin3.setBorder();*/


	//winHost.printWindows();

	//*********************//
	//* Main control loop *//
	//*********************//
	
	int ch = 0;												//Stores typed character
	while((ch = getch()) != KEY_F(10))						//Main control loop. Exit character = F10
	{
		switch(ch)
		{
			case KEY_RESIZE: winHost.resizeWindowHost(COLS, LINES); break;
			case KEY_F(1): testWin1.setDefaultColor(COLOR_PAIR(P_FGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); winHost.printWindows(); break;
			case KEY_F(2): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_FGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); winHost.printWindows(); break;
			case KEY_F(3): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_FGW)); winHost.printWindows(); break;
			case KEY_F(5): winHost.printWindows(); break;
			case KEY_F(6): winHost.resizeWindowHost(COLS/2, LINES/2); break;
			case KEY_F(7): winHost.resizeWindowHost(COLS, LINES); break;
			default: break;
		}
	}



	//************//
	//* Shutdown *//
	//************//

	endwin();

	//******************//
	//* DEBUG END CODE *//
	//******************//

	printf("winHost:  %dx%d at %dx%d\n", winHost.width, winHost.height, winHost.posRow, winHost.posCol);
	printf("testWin1: %dx%d at %dx%d\n", testWin1.width, testWin1.height, testWin1.posRow, testWin1.posCol);
	printf("testWin2: %dx%d at %dx%d\n", testWin2.width, testWin2.height, testWin2.posRow, testWin2.posCol);
	printf("testWin3: %dx%d at %dx%d\n", testWin3.width, testWin3.height, testWin3.posRow, testWin3.posCol);

	//************//
	//* END CODE *//
	//************//

	std::exit(0);
}