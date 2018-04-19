#include "window.h"
#include "color.h"

#include <ncurses.h>

//****************//
//* Window class *//
//****************//

//Base Constructor for the object
Window::Window(int argHeight, int argWidth, int argPosRow, int argPosCol)
{
	height = argHeight;
	width = argWidth;
	posRow = argPosRow;
	posCol = argPosCol;

	defaultColor = COLOR_PAIR(0);

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32);

	contentColorBuffer.reserve(height * width);
	contentColorBuffer.resize(height * width, defaultColor);
}

//Destructor for the object
Window::~Window()
{
	//TODO: Check out how to destruct objects
}

//Sets character at the desired position
//This immediately sets the contentBuffer to the new value
//If no color is specified, default color will be set.
void Window::setCharacter(int row, int col, int newChar) { setCharacter(row, col, newChar, defaultColor); }

void Window::setCharacter(int row, int col, int newChar, int color)
{
	contentBuffer[row * width + col] = newChar;
	contentColorBuffer[row * width + col] = color;
}

//Sets color at the desired position
void Window::setColor(int row, int col, int color) { contentColorBuffer[row * width + col] = color; }

//Gets character at the desired position. Returns the character without any color modifiers
int Window::getCharacter(int row, int col) { return contentBuffer[row * width + col]; }

//Gets character at the desired position. Returns the character with color modifiers
int Window::getCharacterWithColor(int row, int col) { return (contentBuffer[row * width + col] | contentColorBuffer[row * width + col]); }

//Sets the new default color and, refreshes the color buffer
void Window::setDefaultColor(int color)
{
	defaultColor = color;
	for (std::vector<int>::iterator i = contentColorBuffer.begin(); i != contentColorBuffer.end(); ++i)
	{
		*i = defaultColor;
	}
}

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

void printWindows(std::list<Window*> windowList)
{
	erase();
	for(std::list<Window*>::iterator it = windowList.begin(); it != windowList.end(); ++it)
	{
		for (int cRow = 0; cRow < (*(*it)).height; ++cRow)
		{
			move((*(*it)).posRow+cRow, (*(*it)).posCol);
			for (int cCol = 0; cCol < (*(*it)).width; ++cCol)
			{
				addch((*(*it)).getCharacterWithColor(cRow, cCol));
			}
		}
	}
	move(LINES-1, COLS-1);
	refresh();
}