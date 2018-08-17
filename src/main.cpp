#include <iostream>
#include <cstdlib>

#include <ncurses.h>

#include "globalDefine.h"

#include "color.h"
#include "control.h"
#include "container.h"
#include "label.h"

int main()
{
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

	//Setup Controls
	Label testControl;
	testControl.resize(20, 5);
	testControl.setText("Some testing text is here! ye\nboi thiswordissolongitshouldnotfit! something");
	for (int y = 0; y < testControl.getSize().height; ++y)
	{
		move(testControl.getPosition().y + y, testControl.getPosition().x);
		for (int x = 0; x < testControl.getSize().width; ++x)
		{
			addch(testControl.getCharacter(x, y));
		}
	}

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_F(5): {
				werase(stdscr);
				wrefresh(stdscr);
				testControl.setWrap(!testControl.getWrap());
				for (int y = 0; y < testControl.getSize().height; ++y)
				{
					move(testControl.getPosition().y + y, testControl.getPosition().x);
					for (int x = 0; x < testControl.getSize().width; ++x)
					{
						addch(testControl.getCharacter(x, y));
					}
				}
				wrefresh(stdscr);
			} break;
			default: break;
		}
	}

	//Shutdown
	endwin();

	//Debug Info after shutdown
#ifdef __DEBUG__
	//testControl.print();

	Container testContainer;
	testContainer.addControl(&testControl);
	testContainer.draw();
	//testContainer.print();
	//testControl.print();
	//testContainer.resize(2, 2);
	//testContainer.print();
#endif

	std::exit(0);
}