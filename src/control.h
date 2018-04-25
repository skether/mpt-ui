#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

//Base class for control objects.
class Control
{
public:
	int height;												//Height of the control in rows.
	double heightDyn;										//True if the control's height is automatically sized to its parent. If dynamic its a double value between 0 and 1, that specifies the percantage of the parents height, or if its negative then height = parent's height - abs(heightDyn).
	int width;												//Height of the control in cols.
	double widthDyn;										//True if the control's width is automatically sized to its parent. If dynamic its a double value between 0 and 1, that specifies the percantage of the parents width, or if its negative then width = parent's width - abs(widthDyn).
	int posRow;												//Sets which row the control's upper left corner is.
	double posRowDyn;										//True if the control's vertical position is automatically calculated to its parent. If dynamic its a double value between 0 and 1, that specifies the percantage of the parents height.
	int posCol;												//Sets which column the control's upper left corner is.
	double posColDyn;										//True if the control's horizontal position is automatically calculated to its parent. If dynamic its a double value between 0 and 1, that specifies the percantage of the parents width.
	std::vector<int> contentBuffer;							//Stores the character information of the control.
	std::vector<int> contentColorBuffer;					//Stores the color information of the control.

	//Base Constructors for the object.
	//Control has no dynamic sizing properties.
	Control(int argWidth, int argHeight, int argPosRow, int argPosCol);

	//Control has at least one dynamic sizing property.
	Control(double argWidth, double argHeight, double argPosRow, double argPosCol, bool argWidthDyn, bool argHeightDyn, bool argPosRowDyn, bool argPosColDyn, Control *parent);

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