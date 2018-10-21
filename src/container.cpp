#include "container.h"

Container::Container() : Control()
{
	type = ControlType::Container;
	isSelectable = true;
	iSelectedControl = -1;
}

void Container::resize(int argW, int argH)
{
	resizeChildren(argW, argH);
	Control::resize(argW, argH);
}

void Container::draw()
{
	int color = getFocus() ? getDefaultFocusColor() : getDefaultColor();
	for(int y = 0; y < getSize().height; y++)
	{
		for(int x = 0; x < getSize().width; x++)
		{
			setCharacter(x, y, 32);
			setColor(x, y, color);
		}
	}

	Position controlPos;
	Size controlSize;
	for (std::vector<Control*>::iterator i = controls.begin(); i != controls.end(); ++i)
	{
		controlPos = (**i).getPosition();
		controlSize = (**i).getSize();
		for(int y = 0; y < controlSize.height && controlPos.y + y < getSize().height; y++)
		{
			for(int x = 0; x < controlSize.width && controlPos.x + x < getSize().width; x++)
			{
				setCharacter(controlPos.x + x, controlPos.y + y, (**i).getCharacter(x, y));
				inheritColor(controlPos.x + x, controlPos.y + y, (**i).getColor(x, y));
			}
		}
	}

	notifyParent();
}

bool Container::selectPrevChild()
{
	for (int i = iSelectedControl - 1; i >= 0; --i)
	{
		if((*controls[i]).isSelectable)
		{
			if(iSelectedControl != -1) (*controls[iSelectedControl]).setFocus(false);
			(*controls[i]).setFocus(true);
			iSelectedControl = i;
			return true;
		}
	}
	return false;
}

bool Container::selectNextChild()
{
	for (int i = iSelectedControl + 1; i < controls.size(); ++i)
	{
		if((*controls[i]).isSelectable)
		{
			if(iSelectedControl != -1) (*controls[iSelectedControl]).setFocus(false);
			(*controls[i]).setFocus(true);
			iSelectedControl = i;
			return true;
		}
	}
	return false;
}

bool Container::input(int ch)
{
	if(iSelectedControl == -1 && !selectNextChild()) return false;
	else if((*controls[iSelectedControl]).input(ch)) return true;
	else return selfHandleInput(ch);
}

#ifdef __DEBUG__
#include <iostream>
void Container::print(bool isFirst)
{
	if(isFirst) std::cout << ControlTypeToString(type) << "\n";
	std::cout << "\tControls:\tsize(" << controls.size() << "), capacity(" << controls.capacity() << ")\n";
	Control::print(false);
}
#endif