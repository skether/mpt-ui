#include "windowManager.h"

#include "inputHelper.h"

WindowManager::WindowManager(WINDOW* argWindow) { screen = argWindow; child = 0; }

bool WindowManager::input(int ch)
{
	if(child == 0) return false;
	switch(ch)
	{
		case KEY_RESIZE: resize(); break;
		default: if(isCharNav(ch)) if((*child).input(ch)) draw(); break;
	}
	return true;
}

void WindowManager::resize()
{
	if(child != 0) (*child).resize(COLS-1, LINES);
	draw();
}

void WindowManager::draw()
{
	if(child == 0) return;
	werase(screen);
	int heightTarget = (*child).getSize().height;
	int widthTarget = (*child).getSize().width;
	if(heightTarget > LINES) heightTarget = LINES;
	if(widthTarget > COLS) widthTarget = COLS;
	for (int y = 0; y < heightTarget; ++y)
	{
		for (int x = 0; x < widthTarget; ++x)
		{
			attron((*child).getColor(x, y));
			waddch(screen, (*child).getCharacter(x, y));
		}
		waddch(screen, '\n');
	}
	wrefresh(screen);
}