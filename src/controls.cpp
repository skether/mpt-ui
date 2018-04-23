#include <ncurses.h>

#include "controls.h"

//Base class for control objects.
Control::Control(int argHeight, int argWidth, int argPosRow, int argPosCol)
{
	width = argWidth;
	height = argHeight;
	posRow = argPosRow;
	posCol = argPosCol;

	defaultColor = COLOR_PAIR(0);

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32);

	contentColorBuffer.reserve(height * width);
	contentColorBuffer.resize(height * width, defaultColor);
}

//Gets character at the desired position. Returns the character without any color modifiers.
int Control::getCharacter(int row, int col) { return contentBuffer[row * width + col]; }

//Gets character at the desired position. Returns the character with color modifiers.
int Control::getCharacterWithColor(int row, int col) { return (contentBuffer[row * width + col] | contentColorBuffer[row * width + col]); }

//Sets character at the desired position.
//This immediately sets the contentBuffer to the new value.
//If no color is specified, default color will be set.
void Control::setCharacter(int row, int col, int newChar)  { setCharacter(row, col, newChar, defaultColor); }

void Control::setCharacter(int row, int col, int newChar, int color)
{
	contentBuffer[row * width + col] = newChar;
	contentColorBuffer[row * width + col] = color;
}

//Gets color at the desired position. Return the color without the character.
int Control::getColor(int row, int col) { return contentColorBuffer[row * width + col]; }

//Sets color at the desired position.
void Control::setColor(int row, int col, int color) { contentColorBuffer[row * width + col] = color; }

//Sets the new default color and, refreshes the color buffer.
void Control::setDefaultColor(int argColor)
{
	defaultColor = argColor;
	for (std::vector<int>::iterator i = contentColorBuffer.begin(); i != contentColorBuffer.end(); ++i)
	{
		*i = defaultColor;
	}
}