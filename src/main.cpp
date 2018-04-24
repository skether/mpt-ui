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
	testWin1.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin1.setBorder();
	windowList.push_back(&testWin1);

	Window testWin2(LINES, COLS*.2, 0, COLS*.2);
	testWin2.setDefaultColor(COLOR_PAIR(P_BGW));
	testWin2.setBorder();
	windowList.push_back(&testWin2);

	Window testWin3(LINES, COLS-COLS*.4, 0, COLS*.4);
	testWin3.setDefaultColor(COLOR_PAIR(P_FGW));
	testWin3.setBorder();
	windowList.push_back(&testWin3);

	//tun0
	testWin1.setCharacter(1, 1, 't');
	testWin1.setCharacter(1, 2, 'u');
	testWin1.setCharacter(1, 3, 'n');
	testWin1.setCharacter(1, 4, '0');

	//enp3s0f0
	testWin2.setCharacter(1, 1, 'e');
	testWin2.setCharacter(1, 2, 'n');
	testWin2.setCharacter(1, 3, 'p');
	testWin2.setCharacter(1, 4, '3');
	testWin2.setCharacter(1, 5, 's');
	testWin2.setCharacter(1, 6, '0');
	testWin2.setCharacter(1, 7, 'f');
	testWin2.setCharacter(1, 8, '0');

	//enp3s0f1
	testWin2.setCharacter(2, 1, 'e');
	testWin2.setCharacter(2, 2, 'n');
	testWin2.setCharacter(2, 3, 'p');
	testWin2.setCharacter(2, 4, '3');
	testWin2.setCharacter(2, 5, 's');
	testWin2.setCharacter(2, 6, '0');
	testWin2.setCharacter(2, 7, 'f');
	testWin2.setCharacter(2, 8, '1');

	//enp4s0f0
	testWin2.setCharacter(3, 1, 'e');
	testWin2.setCharacter(3, 2, 'n');
	testWin2.setCharacter(3, 3, 'p');
	testWin2.setCharacter(3, 4, '4');
	testWin2.setCharacter(3, 5, 's');
	testWin2.setCharacter(3, 6, '0');
	testWin2.setCharacter(3, 7, 'f');
	testWin2.setCharacter(3, 8, '0');

	//enp4s0f1
	testWin2.setCharacter(4, 1, 'e');
	testWin2.setCharacter(4, 2, 'n');
	testWin2.setCharacter(4, 3, 'p');
	testWin2.setCharacter(4, 4, '4');
	testWin2.setCharacter(4, 5, 's');
	testWin2.setCharacter(4, 6, '0');
	testWin2.setCharacter(4, 7, 'f');
	testWin2.setCharacter(4, 8, '1');

	//Placeholder window for interface settings
	testWin3.setCharacter(1, 1, 'P');
	testWin3.setCharacter(1, 2, 'l');
	testWin3.setCharacter(1, 3, 'a');
	testWin3.setCharacter(1, 4, 'c');
	testWin3.setCharacter(1, 5, 'e');
	testWin3.setCharacter(1, 6, 'h');
	testWin3.setCharacter(1, 7, 'o');
	testWin3.setCharacter(1, 8, 'l');
	testWin3.setCharacter(1, 9, 'd');
	testWin3.setCharacter(1, 10, 'e');
	testWin3.setCharacter(1, 11, 'r');
	testWin3.setCharacter(1, 13, 'w');
	testWin3.setCharacter(1, 14, 'i');
	testWin3.setCharacter(1, 15, 'n');
	testWin3.setCharacter(1, 16, 'd');
	testWin3.setCharacter(1, 17, 'o');
	testWin3.setCharacter(1, 18, 'w');
	testWin3.setCharacter(1, 20, 'f');
	testWin3.setCharacter(1, 21, 'o');
	testWin3.setCharacter(1, 22, 'r');
	testWin3.setCharacter(1, 24, 'i');
	testWin3.setCharacter(1, 25, 'n');
	testWin3.setCharacter(1, 26, 't');
	testWin3.setCharacter(1, 27, 'e');
	testWin3.setCharacter(1, 28, 'r');
	testWin3.setCharacter(1, 29, 'f');
	testWin3.setCharacter(1, 30, 'a');
	testWin3.setCharacter(1, 31, 'c');
	testWin3.setCharacter(1, 32, 'e');
	testWin3.setCharacter(1, 34, 's');
	testWin3.setCharacter(1, 35, 'e');
	testWin3.setCharacter(1, 36, 't');
	testWin3.setCharacter(1, 37, 't');
	testWin3.setCharacter(1, 38, 'i');
	testWin3.setCharacter(1, 39, 'n');
	testWin3.setCharacter(1, 40, 'g');
	testWin3.setCharacter(1, 41, 's');
	testWin3.setCharacter(1, 42, '!');

	for(int i=1; i<testWin1.width-1; i++)
	{
		testWin1.setColor(1, i, COLOR_PAIR(P_BGWH));
	}

	for(int i=1; i<testWin2.width-1; i++)
	{
		testWin2.setColor(1, i, COLOR_PAIR(P_BGWH));
	}

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