#include <ncurses.h>

#include "control.h"

//Base Constructors for the object.
//Control has no dynamic sizing properties.
Control::Control(int argWidth, int argHeight, int argPosRow, int argPosCol) : Control(argWidth, argHeight, argPosRow, argPosCol, false, false, false, false, 0, 0) {}

//Control has at least one dynamic sizing property.
Control::Control(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn, int parWidth, int parHeight)
{

	if(argWidthDyn){ widthDyn = argWidth; } else { width = argWidth; widthDyn = 0; }
	if(argHeightDyn){ heightDyn = argHeight; } else { height = argHeight; heightDyn = 0; }

	if(argPosRowDyn){ posRowDyn = argPosRow; posRow = 0; } else { posRow = argPosRow; posRowDyn = 0; }
	if(argPosColDyn){ posColDyn = argPosCol; posCol = 0; } else { posCol = argPosCol; posColDyn = 0; }

	defaultColor = COLOR_PAIR(0);

	resize(parWidth, parHeight);
}

//Resizes the control
void Control::resize(int parWidth, int parHeight)
{
	if(widthDyn != 0) { width = widthDyn < 0 ? parWidth+widthDyn : parWidth*widthDyn; }
	if(heightDyn != 0) { height = heightDyn < 0 ? parHeight+heightDyn : parHeight*heightDyn; }

	if(posRowDyn != 0) { posRow = posRowDyn < 0 ? posRowDyn : parHeight*posRowDyn; }
	if(posColDyn != 0) { posCol = posColDyn < 0 ? posColDyn : parWidth*posColDyn; }

	///TODO: Might need to null out buffers
	if(contentBuffer.capacity() < (height * width)) { contentBuffer.reserve(height * width * 4); }
	contentBuffer.clear();
	contentBuffer.resize(height * width, 32);

	if(contentColorBuffer.capacity() < (height * width)) { contentColorBuffer.reserve(height * width * 4); }
	contentColorBuffer.clear();
	contentColorBuffer.resize(height * width, defaultColor);

	///TODO: Redraw the control
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