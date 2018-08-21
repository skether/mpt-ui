#include "control.h"

Control::Control()
{
	parent = 0;
	defaultColor = -1;
	defaultFocusColor = -1;
	isFocused = false;
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
	colorMap.resize(size.width * size.height, isFocused ? defaultFocusColor : defaultColor);

	draw();
}

#ifdef __DEBUG__
#include <iostream>
void Control::print(bool isFirst)
{
	if(isFirst) std::cout << "Control:\n";
	std::cout << "\tParent:\t\t" << parent << "\n";
	std::cout << "\tPosition:\tx(" << position.x << "), y(" << position.y << ")\n";
	std::cout << "\tSize:\t\tw(" << size.width << "), h(" << size.height << ")\n";
	std::cout << "\tCharMap:\tsize(" << characterMap.size() << "), capacity(" << characterMap.capacity() << ")\n";
	std::cout << "\tColorMap:\tsize(" << colorMap.size() << "), capacity(" << colorMap.capacity() << ")\n";
	std::cout << "\tDefaultColor:\t" << defaultColor << "\n";
	std::cout << "\tDefaultFocusColor:\t" << defaultFocusColor << "\n";
	std::cout << "\tisFocused:\t" << isFocused << "\n";
}
#endif