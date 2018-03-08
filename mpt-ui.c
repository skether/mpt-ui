#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int main(int argc, char const *argv[])
{
	initscr(); //Initialize screen
	cbreak(); //Disable input buffering
	noecho(); //Dont write input to terminal
	keypad(stdscr, TRUE); //Get all special characters inut

	//move(x, y) //Move the cursor
	wrefresh(stdscr);

	int curX = 0;
	int curY = 0;
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_DOWN: curY++; move(curY, curX); break;
			case KEY_UP: curY--; move(curY, curX); break;
			case KEY_LEFT: curX--; move(curY, curX); break;
			case KEY_RIGHT: curX++; move(curY, curX); break;
			default: break;
		}
		wrefresh(stdscr);
	}

	endwin(); //End the window before exiting
	return 0;
}