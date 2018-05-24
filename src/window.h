#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <list>

#include "control.h"
#include <ncurses.h>

//Base class for window objects
class Window : public Control
{
public:
	std::list<Control*> windowControls;

	//Base Constructors for the object.
	//Control has no dynamic sizing properties.
	Window(int argWidth, int argHeight, int argPosRow, int argPosCol);

	//Control has at least one dynamic sizing property.
	Window(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn, int parWidth, int parHeight);

	//Resizes the control
	void resize(int parWidth, int parHeight);

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder();

	//Adds a control to the window
	void addControl(Control* control);

	//Calculates contentBuffer based on the controls
	void update();
};

//Class for storing windows
class WindowHost : public Control
{
public:
	std::list<Window*> windowList;
	WINDOW *win;

	//Base Constructor for the object
	WindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin);

	//Resizes the control
	void resize(int parWidth, int parHeight);

	//Adds windows to the list
	void addWindow(Window* argWin);

	//Method for printing windows
	void printWindows();

};

#endif