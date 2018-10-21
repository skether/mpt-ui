#ifndef CONTAINER_H
#define CONTAINER_H

#include "control.h"

class Container : public Control
{
public:

	int iSelectedControl;
	std::vector<Control*> controls;

	Container();

	inline void addControl(Control* argControl) { controls.push_back(argControl); argControl->parent = this; resizeChildren(); }

	virtual void setFocus(bool newFocus);

	void resize(int argW, int argH);

	inline void resizeChildren() { resizeChildren(getSize().width, getSize().height); }

	virtual void resizeChildren(int newWidth, int newHeight) = 0;

	inline void inheritColor(int argX, int argY, int argColor) { if(argColor != -1) setColor(argX, argY, argColor); }

	void draw();

	bool selectPrevChild();

	bool selectNextChild();

	virtual bool input(int ch);

	virtual bool selfHandleInput(int ch) = 0;

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

#endif