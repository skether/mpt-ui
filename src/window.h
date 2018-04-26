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
	Window(int argWidth, int argHeight, int argPosRow, int argPosCol, Control *argParent);

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

	//Adds windows to the list
	void addWindow(Window* argWin);

	//Method for printing windows
	void printWindows();

};

#endif