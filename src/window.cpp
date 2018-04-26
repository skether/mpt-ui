#include "window.h"
#include "color.h"

//****************//
//* Window class *//
//****************//

//Base Constructors for the object
Window::Window(int argWidth, int argHeight, int argPosRow, int argPosCol, Control *argParent) : Control(argWidth, argHeight, argPosRow, argPosCol, argParent) {}

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

//Adds a control to the window.
void Window::addControl(Control* control)
{
	windowControls.push_back(control);
}

//Calculates contentBuffer based on the controls.
void Window::update()
{
	for(std::list<Control*>::iterator it = windowControls.begin(); it != windowControls.end(); ++it)
	{
		for (int cRow = 0; cRow < (*(*it)).height; ++cRow)
		{
			for (int cCol = 0; cCol < (*(*it)).width; ++cCol)
			{
				setCharacter(cRow, cCol, 32, COLOR_PAIR(0));
			}
		}
	}
}

//********************//
//* WindowHost class *//
//********************//

//Base Constructor for the object
WindowHost::WindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin) : Control(argWidth, argHeight, argPosRow, argPosCol)
{
	win = argWin;
}

//Adds windows to the list
void WindowHost::addWindow(Window* argWin)
{
	windowList.push_back(argWin);
}

//Prints all windows in the windowList list to the standard screen.
void WindowHost::printWindows()
{
	werase(win);
	for(std::list<Window*>::iterator it = windowList.begin(); it != windowList.end(); ++it)
	{
		for (int cRow = 0; cRow < (*(*it)).height; ++cRow)
		{
			wmove(win, (*(*it)).posRow+cRow, (*(*it)).posCol);
			for (int cCol = 0; cCol < (*(*it)).width; ++cCol)
			{
				waddch(win, (*(*it)).getCharacterWithColor(cRow, cCol));
			}
		}
	}
	wrefresh(win);
}