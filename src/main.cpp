#include <iostream>
#include <cstdlib>
#include <vector>

#include <unistd.h>
#include <ncurses.h>

#include "color.h"

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

	//Base Constructor for the object
	Window(int argHeight, int argWidth, int argPosRow, int argPosCol, int argPosDepth)
	{
		height = argHeight;
		width = argWidth;
		posRow = argPosRow;
		posCol = argPosCol;
		posDepth = argPosDepth;

		contentBuffer.reserve(height * width);
		contentBuffer.resize(height * width, 32);
	}

	//Destructor for the object
	~Window(){
		//TODO: Check out how to destruct objects
	}

	//Sets character at the desired position
	//This immediately sets the contentBuffer to the new value
	void setCharacter(int row, int col, int newChar) { contentBuffer[row * width + col] = newChar; }

	//Gets character at the desired position
	int getCharacter(int row, int col) { return contentBuffer[row * width + col]; }

	//Adds border to the window
	//This immediately sets the contentBuffer to the new values
	void setBorder()
	{
		for (int i = 1; i < height-1; ++i)					//Setting Vertical borders
		{
			setCharacter(i, 0, ACS_VLINE);
			setCharacter(i, width-1, ACS_VLINE);
		}

		for (int i = 1; i < width-1; ++i)					//Setting Horizontal borders
		{
			setCharacter(0, i, ACS_HLINE);
			setCharacter(height-1, i, ACS_HLINE);
		}

		setCharacter(0, 0, ACS_ULCORNER);					//Setting upper left corner
		setCharacter(0, width-1, ACS_URCORNER);				//Setting upper right corner
		setCharacter(height-1, 0, ACS_LLCORNER);			//Setting lower left corner
		setCharacter(height-1, width-1, ACS_LRCORNER);		//Setting lower right corner
	}
};

//Temporary method for printing windows (doesn't respect z-depth)
void printWindow(Window win)
{
	erase();
	for (int cRow = 0; cRow < win.height; ++cRow)
	{
		move(win.posRow+cRow, win.posCol);
		for (int cCol = 0; cCol < win.width; ++cCol)
		{
			addch(win.getCharacter(cRow, cCol));
		}
	}
	refresh();
}

//The programs main entry point
int main()
{
	//**********************//
	//* Initialize ncurses *//
	//**********************//

	initscr();												//Initializing ncurses screen
	cbreak();												//Disable buffering of typed characters
	noecho();												//Disable automatic echoing of typed characters
	keypad(stdscr, true);									//Enable capturing of special keys

	//Check if terminal has color support, if not display error the exit the program.
	//TODO: Right now this projects relies on color support. Black and White only support could be added later.
	if (has_colors() == FALSE)
	{
	    endwin();
	    std::cout << "Your terminal does not support color\n";
	    std::exit(1);
	}

	start_color();											//Initializing ncurses colors
	setupColorPairs();										//Setting up the color pairs. Implemented in color.c



	//**************//
	//* DEBUG CODE *//
	//**************//

	wattron(stdscr, COLOR_PAIR(P_BGW));
	move(0, 0);
	wprintw(stdscr, "BGWINDOW\t\t%d", COLOR_PAIR(P_BGW));

	wattron(stdscr, COLOR_PAIR(P_BGWH));
	move(1, 0);
	wprintw(stdscr, "BGWINDOWHIGHLIGHT\t%d", COLOR_PAIR(P_BGWH));

	wattron(stdscr, COLOR_PAIR(P_FGW));
	move(2, 0);
	wprintw(stdscr, "FGWINDOW\t\t%d", COLOR_PAIR(P_FGW));

	wattron(stdscr, COLOR_PAIR(P_FGWH));
	move(3, 0);
	wprintw(stdscr, "FGWINDOWHIGHLIGHT\t%d", COLOR_PAIR(P_FGWH));

	Window testWindow(20, 50, 2, 15, 0);
	testWindow.setBorder();
	printWindow(testWindow);



	//*********************//
	//* Main control loop *//
	//*********************//
	
	int ch = 0;												//Stores typed character
	while((ch = getch()) != KEY_F(10))						//Main control loop. Exit character = F10
	{
		switch(ch)
		{
			//case KEY_RESIZE: printWindowSize(stdscr); break;
			default: break;
		}
	}



	//************//
	//* Shutdown *//
	//************//

	endwin();
	std::exit(0);
}