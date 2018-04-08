#include "window.h"

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

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32);
}

//Destructor for the object
Window::~Window()
{
	//TODO: Check out how to destruct objects
}

//Sets character at the desired position
//This immediately sets the contentBuffer to the new value
void Window::setCharacter(int row, int col, int newChar) { contentBuffer[row * width + col] = newChar; }

//Gets character at the desired position
int Window::getCharacter(int row, int col) { return contentBuffer[row * width + col]; }

//Adds border to the window
//This immediately sets the contentBuffer to the new values
void Window::setBorder()
{
	for (int i = 1; i < height-1; ++i)					//Setting Vertical borders
	{
		setCharacter(i, 0, ACS_VLINE);
		setCharacter(i, width-1, ACS_VLINE);
	}

	for (int i = 1; i < width-1; ++i)					//Setting Horizontal borders
	{
		setCharacter(0, i, ACS_HLINE);
		setCharacter(height-1, i, ACS_HLINE);
	}

	setCharacter(0, 0, ACS_ULCORNER);					//Setting upper left corner
	setCharacter(0, width-1, ACS_URCORNER);				//Setting upper right corner
	setCharacter(height-1, 0, ACS_LLCORNER);			//Setting lower left corner
	setCharacter(height-1, width-1, ACS_LRCORNER);		//Setting lower right corner
}