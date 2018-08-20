#include <iostream>
#include <cstdlib>

#include <ncurses.h>

#include "globalDefine.h"

#include "color.h"
#include "control.h"
#include "container.h"
#include "stackContainer.h"

#include "label.h"

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
			addch((*ctrl).getCharacter(x, y));
		}
		addch('#');
		addch((y%10)+49);
	}
	wrefresh(stdscr);
}
#endif

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
	VerticalStackContainer testContainer;
	testContainer.resize(70, 20);
	testContainer.addSizingParameter(SizingProperty(2, false));
	testContainer.addSizingParameter(SizingProperty(-1, true));
	testContainer.addSizingParameter(SizingProperty(2, false));

	HorizontalStackContainer horizStack;
	horizStack.addSizingParameter(SizingProperty(15, false));
	horizStack.addSizingParameter(SizingProperty(15, false));

	Label testControl1;
	testControl1.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl1\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");

	Label testControl2;
	testControl2.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");

	Label testControl3;
	testControl3.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl3\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
	
	Label testControl4;
	testControl4.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl4\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");

	horizStack.addControl(&testControl2);
	horizStack.addControl(&testControl4);

	testContainer.addControl(&testControl1);
	testContainer.addControl(&horizStack);
	testContainer.addControl(&testControl3);

	horizStack.draw();
	testContainer.draw();
	testPrint(&testContainer);

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_F(5): testPrint(&testContainer); break;
			default: break;
		}
	}

	//Shutdown
	endwin();

	//Debug Info after shutdown
#ifdef __DEBUG__
	testContainer.print();
	horizStack.print();

	testControl1.print();
	testControl2.print();
	testControl3.print();
	testControl4.print();
#endif

	std::exit(0);
}