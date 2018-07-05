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
	Window(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn);

	//Resizes the control
	virtual void resizeWindow(int argWidth, int argHeight, int argPosRow, int argPosCol) = 0;

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder();

	//Adds a control to the window
	void addControl(Control* control);

	//Calculates contentBuffer based on the controls
	void draw();
};

class TunnelWindow : public Window
{
public:

	//Base Constructors for the object.
	//Control has no dynamic sizing properties.
	TunnelWindow(int argWidth, int argHeight, int argPosRow, int argPosCol);

	//Control has at least one dynamic sizing property.
	TunnelWindow(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn);

	void resizeWindow(int argWidth, int argHeight, int argPosRow, int argPosCol);
};

//Class for storing windows
class WindowHost : public Control
{
public:
	std::vector<Window*> windowList;
	WINDOW *win;

	//Base Constructor for the object
	WindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin);

	//Resizes the control
	virtual void resizeWindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol) = 0;

	//Adds windows to the list
	void addWindow(Window* argWin);

	//Method for printing windows
	void draw();

};

class DefaultWindowHost : public WindowHost
{
public:

	//Base Constructor for the object
	DefaultWindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol, WINDOW* argWin);

	void resizeWindowHost(int argWidth, int argHeight, int argPosRow, int argPosCol);

	void resizeWindowHost(int argWidth, int argHeight);
};

#endif