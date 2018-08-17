#ifndef CONTAINER_H
#define CONTAINER_H

#include "control.h"

class Container : public Control
{
public:

	std::vector<Control*> controls;

	Container();

	inline void addControl(Control* argControl) { controls.push_back(argControl); argControl->parent = this; resizeChildren(); }

	void resize(int argW, int argH);

	inline void resizeChildren() { resizeChildren(getSize().width, getSize().height); }

	virtual void resizeChildren(int newWidth, int newHeight) = 0;

	void draw();

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

#endif