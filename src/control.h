#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

//Base class for control objects.
class Control
{
public:
	int height;												//Height of the control in rows.
	int width;												//Width of the control in rows.
	int posRow;												//Sets which row the control's upper left corner is.
	int posCol;												//Sets which column the control's upper left corner is.
	std::vector<int> contentBuffer;							//Stores the character information of the control.
	std::vector<int> contentColorBuffer;					//Stores the color information of the control.

	//Base Constructor for the object.
	Control(int argHeight, int argWidth, int argPosRow, int argPosCol);

	//Gets character at the desired position. Returns the character without any color modifiers.
	int getCharacter(int row, int col);

	//Gets character at the desired position. Returns the character with color modifiers.
	int getCharacterWithColor(int row, int col);

	//Sets character at the desired position.
	//This immediately sets the contentBuffer to the new value.
	//If no color is specified, default color will be set.
	void setCharacter(int row, int col, int newChar);

	void setCharacter(int row, int col, int newChar, int color);

	//Gets color at the desired position. Return the color without the character.
	int getColor(int row, int col);

	//Sets color at the desired position.
	void setColor(int row, int col, int color);

	//Sets the new default color and, refreshes the color buffer.
	void setDefaultColor(int color);

protected:
	int defaultColor;										//Default colorPair for the control.
};

#endif