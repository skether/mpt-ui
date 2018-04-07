#include <iostream>
#include <cstdlib>
#include <vector>

#include <unistd.h>
#include <ncurses.h>

#include "color.h"

#define nl '\n'

//IMPLEMENTING WINDOWS
class Window
{
public:
	int height;
	int width;
	int posRow;
	int posCol;
	int posDepth;
	//int* content = NULL;
	std::vector<int> content;

	Window(int argHeight, int argWidth, int argPosRow, int argPosCol, int argPosDepth)
	{
		height = argHeight;
		width = argWidth;
		posRow = argPosRow;
		posCol = argPosCol;
		posDepth = argPosDepth;

		content.reserve(height * width);
		content.resize(height * width, 32);


		/*if(!(content = new int[height * width]))
		{
			std::cout << "Error: Out of memory!\n";
			std::exit(1);
		}*/

		/*for (int i = 0; i < height*width; ++i)
		{
			content[i] = 32; //Fills the array with spaces
		}*/
	}

	~Window(){}

	void setCharacter(int row, int col, int newChar)
	{
		content[row*width+col] = newChar;
	}

	int getCharacter(int row, int col)
	{
		return content[row*width+col];
	}

	void setBorder()
	{
		for (int i = 1; i < height-1; ++i)
		{
			//setCharacter(i, 0, i+48);
			setCharacter(i, 0, ACS_VLINE);
			setCharacter(i, width-1, ACS_VLINE);
		}

		for (int i = 1; i < width-1; ++i)
		{
			setCharacter(0, i, ACS_HLINE);
			setCharacter(height-1, i, ACS_HLINE);
		}

		setCharacter(0, 0, ACS_ULCORNER);
		setCharacter(0, width-1, ACS_URCORNER);
		setCharacter(height-1, 0, ACS_LLCORNER);
		setCharacter(height-1, width-1, ACS_LRCORNER);
	}
};

void printWindow(Window win)
{
	erase();
	for (int cRow = 0; cRow < win.height; ++cRow)
	{
		move(win.posRow+cRow, win.posCol);
		for (int cCol = 0; cCol < win.width; ++cCol)
		{
			move(0, 0);
			printw("cRow: %4d", cRow);
			move(1, 0);
			printw("cCol: %4d", cCol);
			move(win.posRow+cRow, win.posCol+cCol);
			//if(cCol == 0) addch(cRow+48);
			/*else*/ addch(win.getCharacter(cRow, cCol));
			refresh();
			/*usleep(100000);
			if(cRow == 1) usleep(400000);*/
		}
	}
	refresh();
}

//MAIN CLASS
int main()
{
	//std::cout << "Hello world!" << nl;

	//Init ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

	if (has_colors() == FALSE)
	{
	    endwin();
	    std::cout << "Your terminal does not support color\n";
	    std::exit(1);
	}

	start_color();
	setupColorPairs();

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
	//testWindow.setCharacter(0, 0, 48);
	printWindow(testWindow);
	//addch(testWindow.getCharacter(1, 29));

	//MAIN LOOP
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			//case KEY_RESIZE: printWindowSize(stdscr); break;
			//case : printWindow(testWindow); break;
			default: break;
		}
	}

	endwin();

	std::cout << "testWindow.content[i]\r\n";
	for (int i = 0; i < testWindow.height*testWindow.width; ++i)
	{
		if(testWindow.content[i] != 32)
		std::cout << i << ":\t" << testWindow.content[i] << "\r\n";
	}

	std::cout << "\r\ntestWindow.getCharacter(i, j)\r\n";
	for (int i = 0; i < testWindow.height; ++i)
	{
		for (int j = 0; j < testWindow.width; ++j)
		{
			if(testWindow.getCharacter(i, j) != 32)
				std::cout << i << ", " << j << ":\t" << testWindow.getCharacter(i, j) << "\r\n";
		}
		
	}

	std::exit(0);
}