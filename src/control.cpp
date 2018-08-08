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
void Control::print()
{
	printf("Control:\n");
	printf("\tPosition:\tx(%d), y(%d)\n", position.x, position.y);
	printf("\tSize:\t\tw(%d), h(%d)\n", size.width, size.height);
	printf("\tCharMap:\tsize(%ld), capacity(%ld)\n", characterMap.size(), characterMap.capacity());
	printf("\tColorMap:\tsize(%ld), capacity(%ld)\n", colorMap.size(), colorMap.capacity());
	printf("\tDefaultColor:\t%d\n", defaultColor);
}
#endif