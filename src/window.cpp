#include "window.h"
#include "color.h"

#include <ncurses.h>

//****************//
//* Window class *//
//****************//

//Base Constructor for the object
Window::Window(int argHeight, int argWidth, int argPosRow, int argPosCol, int argPosDepth)
{
	height = argHeight;
	width = argWidth;
	posRow = argPosRow;
	posCol = argPosCol;
	posDepth = argPosDepth;

	defaultColor = COLOR_PAIR(P_BGW);

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32 | defaultColor);
}

//Destructor for the object
Window::~Window()
{
	//TODO: Check out how to destruct objects
}

//Sets character at the desired position
//This immediately sets the contentBuffer to the new value
void Window::setCharacter(int row, int col, int newChar) { contentBuffer[row * width + col] = newChar; }

void Window::setCharacter(int row, int col, int newChar, int color) { contentBuffer[row * width + col] = (newChar | color); }

//Gets character at the desired position
int Window::getCharacter(int row, int col) { return contentBuffer[row * width + col]; }

//Adds border to the window
//This immediately sets the contentBuffer to the new values
void Window::setBorder()
{
	for (int i = 1; i < height-1; ++i)									//Setting Vertical borders
	{
		setCharacter(i, 0, ACS_VLINE, defaultColor);
		setCharacter(i, width-1, ACS_VLINE, defaultColor);
	}

	for (int i = 1; i < width-1; ++i)									//Setting Horizontal borders
	{
		setCharacter(0, i, ACS_HLINE, defaultColor);
		setCharacter(height-1, i, ACS_HLINE, defaultColor);
	}

	setCharacter(0, 0, ACS_ULCORNER, defaultColor);						//Setting upper left corner
	setCharacter(0, width-1, ACS_URCORNER, defaultColor);				//Setting upper right corner
	setCharacter(height-1, 0, ACS_LLCORNER, defaultColor);				//Setting lower left corner
	setCharacter(height-1, width-1, ACS_LRCORNER, defaultColor);		//Setting lower right corner
}

void printWindows(std::list windowList)
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