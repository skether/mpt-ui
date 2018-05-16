#include <ncurses.h>

#include "control.h"

//Base Constructors for the object.
//Control has no dynamic sizing properties.
Control::Control(int argWidth, int argHeight, int argPosRow, int argPosCol, Control *argParent) : Control(argWidth, argHeight, argPosRow, argPosCol, false, false, false, false, argParent) {}

//Control has at least one dynamic sizing property.
Control::Control(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn, Control* argParent)
{

	if(argWidthDyn){width = argWidth < 0 ? argParent->width+argWidth : argParent->width*argWidth; } else {width = argWidth; }
	if(argHeightDyn){height = argHeight < 0 ? argParent->height+argHeight : argParent->height*argHeight; } else {height = argHeight; }

	if(argPosRowDyn){posRow = argPosRow < 0 ? argParent->posRow+argPosRow : argParent->posRow*argPosRow; } else {posRow = argPosRow; }
	if(argPosColDyn){posCol = argPosCol < 0 ? argParent->posCol+argPosCol : argParent->posCol*argPosCol; } else {posCol = argPosCol; }

	defaultColor = COLOR_PAIR(0);

	contentBuffer.reserve(height * width);
	contentBuffer.resize(height * width, 32);

	contentColorBuffer.reserve(height * width);
	contentColorBuffer.resize(height * width, defaultColor);

	printf("Control::Control End\n");
}

//Constructor for WindowHost objects
Control::Control(int argWidth, int argHeight, int argPosRow, int argPosCol)
{
	width = argWidth;
	height = argHeight;
	posRow = argPosRow;
	posCol = argPosCol;

	parent = NULL;

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