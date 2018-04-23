#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

#include <ncurses.h>

#include "color.h"
#include "windows.h"

//Temporary method for printing windows (doesn't respect z-depth)
void printWindow(Window win)
{
	erase();
	for (int cRow = 0; cRow < win.height; ++cRow)
	{
		move(win.posRow+cRow, win.posCol);
		for (int cCol = 0; cCol < win.width; ++cCol)
		{
			addch(win.getCharacter(cRow, cCol));
		}
	}
	refresh();
}

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



	//**************//
	//* DEBUG CODE *//
	//**************//

	/*wattron(stdscr, COLOR_PAIR(P_BGW));
	move(0, 0);
	wprintw(stdscr, "BGWINDOW\t\t%d", COLOR_PAIR(P_BGW));

	wattron(stdscr, COLOR_PAIR(P_BGWH));
	move(1, 0);
	wprintw(stdscr, "BGWINDOWHIGHLIGHT\t%d", COLOR_PAIR(P_BGWH));

	wattron(stdscr, COLOR_PAIR(P_FGW));
	move(2, 0);
	wprintw(stdscr, "FGWINDOW\t\t%d", COLOR_PAIR(P_FGW));

	wattron(stdscr, COLOR_PAIR(P_FGWH));
	move(3, 0);
	wprintw(stdscr, "FGWINDOWHIGHLIGHT\t%d", COLOR_PAIR(P_FGWH));*/

	std::list<Window*> windowList;

	Window testWin1(LINES, COLS*.2, 0, 0);
	testWin1.setDefaultColor(COLOR_PAIR(P_FGW));
	testWin1.setBorder();
	windowList.push_back(&testWin1);

	Window testWin2(LINES, COLS*.2, 0, COLS*.2);
	testWin2.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin2.setBorder();
	windowList.push_back(&testWin2);

	Window testWin3(LINES, COLS-COLS*.4, 0, COLS*.4);
	testWin3.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin3.setBorder();
	windowList.push_back(&testWin3);

	printWindows(windowList);



	//*********************//
	//* Main control loop *//
	//*********************//
	
	int ch = 0;												//Stores typed character
	while((ch = getch()) != KEY_F(10))						//Main control loop. Exit character = F10
	{
		switch(ch)
		{
			//case KEY_RESIZE: printWindowSize(stdscr); break;
			case KEY_F(1): testWin1.setDefaultColor(COLOR_PAIR(P_FGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); printWindows(windowList); break;
			case KEY_F(2): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_FGW)); testWin3.setDefaultColor(COLOR_PAIR(P_BGW)); printWindows(windowList); break;
			case KEY_F(3): testWin1.setDefaultColor(COLOR_PAIR(P_BGW)); testWin2.setDefaultColor(COLOR_PAIR(P_BGW)); testWin3.setDefaultColor(COLOR_PAIR(P_FGW)); printWindows(windowList); break;
			default: break;
		}
	}



	//************//
	//* Shutdown *//
	//************//

	endwin();
	std::exit(0);
}