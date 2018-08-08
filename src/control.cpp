#include "control.h"

#include <ncurses.h>

Control::Control()
{
	defaultColor = -1; //Transparent
}

void Control::resize(int argW, int argH)
{
	size.width = argW;
	size.height = argH;

	if(characterMap.capacity() < unsigned(size.width * size.height))
		characterMap.reserve(size.width * size.height * 4);
	characterMap.clear();
	characterMap.resize(size.width * size.height, 32);

	if(colorMap.capacity() < unsigned(size.width * size.height))
		colorMap.reserve(size.width * size.height * 4);
	colorMap.clear();
	colorMap.resize(size.width * size.height, defaultColor);

	draw();
}

#ifdef __DEBUG__
#include <iostream>
void Control::print(bool isFirst)
{
	if(isFirst) std::cout << "Control:\n";
	std::cout << "\tPosition:\tx(" << position.x << "), y(" << position.y << ")\n";
	std::cout << "\tSize:\t\tw(" << size.width << "), h(" << size.height << ")\n";
	std::cout << "\tCharMap:\tsize(" << characterMap.size() << "), capacity(" << characterMap.capacity() << ")\n";
	std::cout << "\tColorMap:\tsize(" << colorMap.size() << "), capacity(" << colorMap.capacity() << ")\n";
	std::cout << "\tDefaultColor:\t" << defaultColor << "\n";
}
#endif