#include "window.h"
#include "color.h"

//****************//
//* Window class *//
//****************//

//Base Constructors for the object
//Control has no dynamic sizing properties.
Window::Window(int argWidth, int argHeight, int argPosRow, int argPosCol) : Control(argWidth, argHeight, argPosRow, argPosCol) {}

//Control has at least one dynamic sizing property.
Window::Window(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn) : Control(argWidth, argHeight, argPosRow, argPosCol, argWidthDyn, argHeightDyn, argPosRowDyn, argPosColDyn) {}

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

//***********************//
//* Tunnel Window class *//
//***********************//

//Base Constructors for the object
//Control has no dynamic sizing properties.
TunnelWindow::TunnelWindow(int argWidth, int argHeight, int argPosRow, int argPosCol) : Window(argWidth, argHeight, argPosRow, argPosCol) {}

//Control has at least one dynamic sizing property.
TunnelWindow::TunnelWindow(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn) : Window(argWidth, argHeight, argPosRow, argPosCol, argWidthDyn, argHeightDyn, argPosRowDyn, argPosColDyn) {}

void TunnelWindow::resizeWindow(int argWidth, int argHeight, int argPosRow, int argPosCol)
{
	resizeControl(argWidth, argHeight, argPosRow, argPosCol);

	setBorder();

	//Stuff goes here on how to resize controls
	//Since controls are not yet implemented nothing is here
}

//********************//
//* WindowHost class *//
//********************//

//Base Constructor for the object
WindowHost::WindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin) : Control(argWidth, argHeight, argPosRow, argPosCol)
{
	win = argWin;
	windowList.reserve(10);
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
	wrefresh(win);
	for(std::vector<Window*>::iterator it = windowList.begin(); it != windowList.end(); ++it)
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

//***************************//
//* DefaultWindowHost class *//
//***************************//

//Base Constructor for the object
DefaultWindowHost::DefaultWindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin) : WindowHost(argWidth, argHeight, argPosRow, argPosCol, argWin) {}

void DefaultWindowHost::resizeWindowHost(int argWidth, int argHeight)
{
	resizeWindowHost(argWidth, argHeight, 0, 0);
}

void DefaultWindowHost::resizeWindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol)
{
	resizeControl(argWidth, argHeight, argPosRow, argPosCol);

	//Stuff goes here on how to resize windows
	(*(windowList[0])).resizeWindow(argWidth*.2, argHeight, 0, 0);
	(*(windowList[1])).resizeWindow(argWidth*.2, argHeight, 0, (*(windowList[0])).width);
	(*(windowList[2])).resizeWindow(argWidth-((*(windowList[1])).width+(*(windowList[1])).posCol)-1, argHeight, 0, (*(windowList[1])).width+(*(windowList[1])).posCol);

	printWindows();
}

/*//Resizes the control
void Window::resize(int parWidth, int parHeight){
	Control::resize(parWidth, parHeight);

	for(std::list<Control*>::iterator it = windowControls.begin(); it != windowControls.end(); ++it)
	{
		(*(*it)).resize(width, height);
	}

	setBorder();

	update();
}*/

/*if(widthDyn != 0) { width = widthDyn < 0 ? parWidth+widthDyn : parWidth*widthDyn; }
	if(heightDyn != 0) { height = heightDyn < 0 ? parHeight+heightDyn : parHeight*heightDyn; }

	if(posRowDyn != 0) { posRow = posRowDyn < 0 ? posRowDyn : parHeight*posRowDyn; }
	if(posColDyn != 0) { posCol = posColDyn < 0 ? posColDyn : parWidth*posColDyn; }
*/

/*//Resizes the control
void WindowHost::resize(int newWidth, int newHeight){
	width = newWidth;
	height = newHeight;

	Control::resize(0, 0);

	for(std::list<Window*>::iterator it = windowList.begin(); it != windowList.end(); ++it)
	{
		(*(*it)).resize(width, height);
	}

	printWindows();
}*/