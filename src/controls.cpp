#include <ncurses.h>

#include "controls.h"

Control::Control(int argHeight, int argWidth, int argPosRow, int argPosCol)
{
	width = argWidth;
	height = argHeight;
	posRow = argPosRow;
	posCol = argPosCol;

	color = COLOR_PAIR(0);

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32);

	contentColorBuffer.reserve(height * width);
	contentColorBuffer.resize(height * width, color);
}

void Control::setColor(int argColor)
{
	color = argColor;
	for (std::vector<int>::iterator i = contentColorBuffer.begin(); i != contentColorBuffer.end(); ++i)
	{
		*i = color;
	}
}