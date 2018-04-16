#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

//Base class for window objects
class Window
{
public:
	int height;												//Height of the window in rows
	int width;												//Width of the window in rows
	int posRow;												//Sets which row the window's upper left corner is.
	int posCol;												//Sets which column the window's upper left corner is.
	int posDepth;											//Sets the z-depth of the window
	std::vector<int> contentBuffer;							//Stores the character information of the window

	int defaultColor;										//Default colorPair for the window

	//Base Constructor for the object
	Window(int argHeight, int argWidth, int argPosRow, int argPosCol, int argPosDepth);

	//Destructor for the object
	~Window();

	//Sets character at the desired position
	//This immediately sets the contentBuffer to the new value
	void setCharacter(int row, int col, int newChar);

	void setCharacter(int row, int col, int newChar, int color);

	//Gets character at the desired position
	int getCharacter(int row, int col);

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder();
};

#endif