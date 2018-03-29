#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "door.h"

struct DOOR
{
	int x;
	int y;
	int z;
	int h;
	int w;
	int *content;
};

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