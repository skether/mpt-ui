#ifndef WINDOWS_H
#define WINDOWS_H

#include <vector>
#include <list>

#include "controls.h"

//Base class for window objects
class Window : public Control
{
public:
	std::list<Control*> windowControls;

	//Base Constructor for the object.
	Window(int argHeight, int argWidth, int argPosRow, int argPosCol);

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder();

	//Adds a control to the window
	void addControl(Control* control);

	//Calculates contentBuffer based on the controls
	void update();
};

//Method for printing windows
void printWindows(std::list<Window*> windowList);

#endif