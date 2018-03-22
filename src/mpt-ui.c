#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct DOOR
{
	int x;
	int y;
	int z;
	int h;
	int w;
	int *content;
} door;

door* initDoor(int argx, int argy, int argz, int argh, int argw)
{
	door *cdoor;
	cdoor = malloc(sizeof(door));
	cdoor->x = argx;
	cdoor->y = argy;
	cdoor->z = argz;
	cdoor->h = argh;
	cdoor->w = argw;
	cdoor->content = calloc(cdoor->h*cdoor->w, sizeof(int));
	memset(cdoor->content, 32, cdoor->h*cdoor->w*sizeof(int)); //Fills the array with spaces
	return cdoor;
}

void addBorder(door* cdoor)
{
	for (int i = 0; i < cdoor->h; i++)
	{
		cdoor->content[i*cdoor->w + 		 0] = ACS_VLINE;
		//cdoor->content[i*cdoor->w + 		 0] = i+48;
		cdoor->content[i*cdoor->w + cdoor->w-1] = ACS_VLINE;
	}

	for (int j = 0; j < cdoor->w; j++)
	{
		cdoor->content[j] = ACS_HLINE;
		cdoor->content[(cdoor->h-1)*cdoor->w + j] = ACS_HLINE;
	}

	cdoor->content[0] = ACS_ULCORNER;
	cdoor->content[cdoor->w-1] = ACS_URCORNER;
	cdoor->content[(cdoor->h-1)*cdoor->w] = ACS_LLCORNER;
	cdoor->content[(cdoor->h-1)*cdoor->w + cdoor->w-1] = ACS_LRCORNER;
}

void printDoor(door* cdoor, WINDOW *win)
{
	werase(win);
	for (int i = 0; i < cdoor->h; i++)
	{
		wmove(win, cdoor->x+i, cdoor->y);
		for (int j = 0; j < cdoor->w; j++)
		{
			waddch(win, cdoor->content[i*cdoor->w + j]);
		}
	}
	wrefresh(win);
}

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

	door *testDoor;
	testDoor = initDoor(2, 2, 0, 20, 50);

	addBorder(testDoor);
	printDoor(testDoor, stdscr);

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
	return 0;
}