#include "container.h"

Container::Container() : Control() {}

void Container::resize(int argW, int argH)
{
	resizeChildren(argW, argH);
	Control::resize(argW, argH);
}

void Container::draw()
{
	for(int y = 0; y < getSize().height; y++)
	{
		for(int x = 0; x < getSize().width; x++)
		{
			setCharacter(x, y, 32);
			setColor(x, y, -1);
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
				setColor(controlPos.x + x, controlPos.y + y, (**i).getColor(x, y));
			}
		}
	}
}

#ifdef __DEBUG__
#include <iostream>
void Container::print(bool isFirst)
{
	if(isFirst) std::cout << "Container:\n";
	std::cout << "\tControls:\tsize(" << controls.size() << "), capacity(" << controls.capacity() << ")\n";
	Control::print(false);
}
#endif