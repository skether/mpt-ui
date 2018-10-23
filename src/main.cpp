#include <iostream>
#include <cstdlib>

#include <ncurses.h>

#include "globalDefine.h"
#include "inputHelper.h"

#include "windowManager.h"
#include "color.h"
#include "control.h"
#include "container.h"
#include "stackContainer.h"

#include "spacer.h"
#include "label.h"
#include "textBox.h"

#ifdef __DEBUG__
void testPrint(Control* ctrl)
{
	werase(stdscr);
	wrefresh(stdscr);
	for (int y = 0; y < (*ctrl).getSize().height; ++y)
	{
		move((*ctrl).getPosition().y + y, (*ctrl).getPosition().x);
		for (int x = 0; x < (*ctrl).getSize().width; ++x)
		{
			addch((*ctrl).getCharacterForPrinting(x, y));
		}
	}
	wrefresh(stdscr);
}
#endif

int main()
{
#ifdef __DEBUG__
	//Delete debugLog.txt file's contents!
	_debugErase();
#endif

	//Init ncurses
	initscr();	//Init screen
	cbreak();	//Disable input buffering
	noecho();	//Disable input reflection
	keypad(stdscr, true);	//Enable special character capture
	curs_set(0);	//Hide the cursor

	if(has_colors() == false) //Check if terminal has color support
	{
		endwin();
		std::cout << "Your terminal does not support color!\n";
		std::exit(1);
	}
	start_color();
	setupColors();

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{

	}

	//Shutdown
	endwin();

#ifdef __DEBUG__
	//Debug info after shutdown

#endif

	std::exit(0);
}