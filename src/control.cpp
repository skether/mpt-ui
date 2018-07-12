#include <ncurses.h>

#include "control.h"

//Base Constructors for the object.
//Control has no dynamic sizing properties.
Control::Control(int argWidth, int argHeight, int argPosRow, int argPosCol) : Control(argWidth, argHeight, argPosRow, argPosCol, false, false, false, false) {}

//Control has at least one dynamic sizing property.
Control::Control(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn)
{

	if(argWidthDyn){ widthDyn = argWidth; } else { width = argWidth; widthDyn = 0; }
	if(argHeightDyn){ heightDyn = argHeight; } else { height = argHeight; heightDyn = 0; }

	if(argPosRowDyn){ posRowDyn = argPosRow; } else { posRow = argPosRow; posRowDyn = 0; }
	if(argPosColDyn){ posColDyn = argPosCol; } else { posCol = argPosCol; posColDyn = 0; }

	defaultColor = COLOR_PAIR(0);
}

//Resizes the control
void Control::resizeControl(int argWidth, int argHeight, int argPosRow, int argPosCol)
{
	width = argWidth;
	height = argHeight;
	posRow = argPosRow;
	posCol = argPosCol;

	if(contentBuffer.capacity() < (height * width)) { contentBuffer.reserve(height * width * 4); }
	contentBuffer.clear();
	contentBuffer.resize(height * width, 32);

	if(contentColorBuffer.capacity() < (height * width)) { contentColorBuffer.reserve(height * width * 4); }
	contentColorBuffer.clear();
	contentColorBuffer.resize(height * width, defaultColor);

	draw();
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

//***************//
//* Label class *//
//***************//

//Base Constructors for the object.
//Control has no dynamic sizing properties.
Label::Label(int argWidth, int argHeight, int argPosRow, int argPosCol, std::string argText) : Control(argWidth, argHeight, argPosRow, argPosCol)
{
	text = argText;
}

//Control has at least one dynamic sizing property.
Label::Label(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn, std::string argText) : Control(argWidth, argHeight, argPosRow, argPosCol, argWidthDyn, argHeightDyn, argPosRowDyn, argPosColDyn)
{
	text = argText;
}

//Returns the current text stored in the label.
std::string Label::getText() { return text; }

//Sets the current text stored in the label.
void Label::setText(std::string value) { text = value; }

//Draws the control to the buffer
void Label::draw()
{
	int stringIndex = 0;
	for(int cRow = 0; cRow < height; cRow++)
	{
		for(int cCol = 0; cCol < width; cCol++)
		{
			if(stringIndex < text.length())
			{
				setCharacter(cRow, cCol, text[stringIndex]);
				stringIndex++;
			}
			else
			{
				setCharacter(cRow, cCol, 32);
			}
		}
	}
}
