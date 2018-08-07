#include <iostream>
#include <cstdlib>

#include <ncurses.h>

#include "globalDefine.h"

#include "color.h"

int main()
{
	//Init ncurses
	initscr();	//Init screen
	cbreak();	//Disable input buffering
	noecho();	//Disable input reflection
	keypad(stdscr, true);	//Enable special character capture
	curs_set(0);	//Hide the cursor

	if(has_colors() == false) //Check if terminal has color support
	{
		endwin();
		std::cout << "Your terminal does not support color!\n";
		std::exit(1);
	}
	start_color();
	setupColors();

	//Setup Controls
	addstr("Test!");

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			default: break;
		}
	}

	//Shutdown
	endwin();

	//Debug Info after shutdown
#ifdef __DEBUG__
#endif

	std::exit(0);
}