#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "door.h"
#include "colornames.h"

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

	init_color(CN_BGWBG, CC_BGWBG);
	init_pair(P_BGW, COLOR_WHITE, CN_BGWBG);

	init_color(CN_BGWBGH, CC_BGWBGH);
	init_pair(P_BGWH, COLOR_GREEN, CN_BGWBGH);

	init_color(CN_FGWBG, CC_FGWBG);
	init_pair(P_FGW, COLOR_WHITE, CN_FGWBG);

	init_color(CN_FGWBGH, CC_FGWBGH);
	init_pair(P_FGWH, COLOR_BLACK, CN_FGWBGH);

	wattron(stdscr, COLOR_PAIR(P_BGW));
	move(0, 0);
	wprintw(stdscr, "BGWINDOW");

	wattron(stdscr, COLOR_PAIR(P_BGWH));
	move(1, 0);
	wprintw(stdscr, "BGWINDOWHIGHLIGHT");

	wattron(stdscr, COLOR_PAIR(P_FGW));
	move(2, 0);
	wprintw(stdscr, "FGWINDOW");

	wattron(stdscr, COLOR_PAIR(P_FGWH));
	move(3, 0);
	wprintw(stdscr, "FGWINDOWHIGHLIGHT");

	//door *testDoor;
	//testDoor = initDoor(0, 0, 0, LINES, COLS);

	//addBorder(testDoor);
	//printDoor(testDoor, stdscr);

	//printf("%d\n", ACS_HLINE);

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
	exit(0);
}