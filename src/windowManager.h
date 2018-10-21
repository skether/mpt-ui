#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "container.h"
#include <ncurses.h>

class WindowManager
{
private:

	Container* child;
	WINDOW* screen;

public:

	WindowManager(WINDOW* argWindow);

	inline void setChild(Container* newChild) { child = newChild; resize(); draw(); }

	inline Container* getChild() { return child; }

	bool input(int ch);

	void resize();

	void draw();
};

#endif