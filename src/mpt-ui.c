#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "door.h"
#include "color.h"

void printWindowSize(WINDOW* win)
{
	werase(win);
	wmove(win, 0, 0);
	wprintw(win, "Height: %d", LINES);
	wmove(win, 1, 0);
	wprintw(win, "Width:  %d", COLS);
	wrefresh(win);
}

int main(int argc, char const *argv[])
{
  //Init
	initscr(); //Initialize screen
	cbreak(); //Disable input buffering
	noecho(); //Dont write input to terminal
	keypad(stdscr, TRUE); //Get all special characters input

	if (has_colors() == FALSE)
	{
	    endwin();
	    printf("Your terminal does not support color\n");
	    exit(1);
	}

	start_color();
	setupColorPairs();
  
  //Testing Colors
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

	//door *testDoor;
	//testDoor = initDoor(0, 0, 0, LINES, COLS);

	//addBorder(testDoor);
	//printDoor(testDoor, stdscr);

	//MAIN LOOP
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_RESIZE: printWindowSize(stdscr); break;
			default: break;
		}
	}

	endwin(); //End the window before exiting
	return 0;
}