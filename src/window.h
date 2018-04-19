#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <list>

//Base class for window objects
class Window
{
public:
	int height;												//Height of the window in rows
	int width;												//Width of the window in rows
	int posRow;												//Sets which row the window's upper left corner is.
	int posCol;												//Sets which column the window's upper left corner is.
	std::vector<int> contentBuffer;							//Stores the character information of the window
	std::vector<int> contentColorBuffer;					//Stores the color information of the window.

	//Base Constructor for the object
	Window(int argHeight, int argWidth, int argPosRow, int argPosCol);

	//Destructor for the object
	~Window();

	//Sets character at the desired position
	//This immediately sets the contentBuffer to the new value
	//If no color is specified, default color will be set.
	void setCharacter(int row, int col, int newChar);

	void setCharacter(int row, int col, int newChar, int color);

	//Sets color at the desired position
	void setColor(int row, int col, int color);

	//Gets character at the desired position. Returns the character without any color modifiers
	int getCharacter(int row, int col);

	//Gets character at the desired position. Returns the character with color modifiers
	int getCharacterWithColor(int row, int col);

	//Sets the new default color and, refreshes the color buffer
	void setDefaultColor(int color);

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder();

private:
	int defaultColor;										//Default colorPair for the window
};

//Method for printing windows
void printWindows(std::list<Window*> windowList);

#endif