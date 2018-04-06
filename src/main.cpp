#include <iostream>
#include <ncurses.h>
#include "color.h"

#define nl '\n'

int main()
{
	//std::cout << "Hello world!" << nl;

	//Init ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

	if (has_colors() == FALSE)
	{
	    endwin();
	    printf("Your terminal does not support color\n");
	    return 1;
	}

	start_color();
	color::setupColorPairs();

	wattron(stdscr, COLOR_PAIR(P_BGW));
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
	wprintw(stdscr, "FGWINDOWHIGHLIGHT\t%d", COLOR_PAIR(P_FGWH));

	//MAIN LOOP
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			//case KEY_RESIZE: printWindowSize(stdscr); break;
			default: break;
		}
	}

	endwin();
	return 0;
}