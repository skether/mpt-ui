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

	WindowHost winHost(COLS, LINES, 0, 0, stdscr);

	Window testWin1(.2, 1, 0, 0, true, true, false, true, winHost.width, winHost.height);
	testWin1.setDefaultColor(COLOR_PAIR(P_FGW));
	testWin1.setBorder();
	winHost.addWindow(&testWin1);

	Window testWin2(.2, 1, 0, .2, true, true, false, true, winHost.width, winHost.height);
	testWin2.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin2.setBorder();
	winHost.addWindow(&testWin2);

	Window testWin3(.6, 1, 0, .4, true, true, false, true, winHost.width, winHost.height);
	testWin3.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin3.setBorder();
	winHost.addWindow(&testWin3);

	winHost.printWindows();

	//*********************//
	//* Main control loop *//
	//*********************//
	
	int ch = 0;												//Stores typed character
	while((ch = getch()) != KEY_F(10))						//Main control loop. Exit character = F10
	{
		switch(ch)
		{
			//case KEY_RESIZE: printWindowSize(stdscr); break;
			case KEY_F(1): testWin1.setDefaultColor(COLOR_PAIR(P_FGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); winHost.printWindows(); break;
			case KEY_F(2): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_FGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); winHost.printWindows(); break;
			case KEY_F(3): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_FGW)); winHost.printWindows(); break;
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

	

	//************//
	//* END CODE *//
	//************//

	std::exit(0);
}