#include <iostream>
#include <cstdlib>

#include <ncurses.h>

#include "globalDefine.h"
#include "inputHelper.h"

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
	//Delete debugLog.txt file's contents!
	_debugErase();

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
	testContainer.resize(COLS, LINES);
	testContainer.addSizingParameter(SizingProperty(2, false));
	testContainer.addSizingParameter(SizingProperty(-1, true));
	testContainer.addSizingParameter(SizingProperty(5, false));
	testContainer.setDefaultColor(Color_Window_Inactive_Normal);
	testContainer.setDefaultFocusColor(Color_Window_Active_Normal);

	VerticalStackContainer middleStack;
	middleStack.addSizingParameter(SizingProperty(1, false));
	middleStack.addSizingParameter(SizingProperty(-1, true));

	HorizontalStackContainer horizStack;
	horizStack.addSizingParameter(SizingProperty(15, false));
	horizStack.addSizingParameter(SizingProperty(-1, true));
	horizStack.addSizingParameter(SizingProperty(15, false));

	Label testControl1;
	testControl1.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl1\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
	testControl1.setDefaultFocusColor(Color_Window_Active_Normal);
	testControl1.isSelectable = true;

	Label testControl2;
	testControl2.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
	testControl2.setDefaultFocusColor(Color_Window_Active_Normal);
	testControl2.isSelectable = true;

	Label testControl3;
	testControl3.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl3\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
	testControl3.setDefaultFocusColor(Color_Window_Active_Normal);
	testControl3.isSelectable = true;
	
	Label testControl4;
	testControl4.setText("1234567890123456789012345678901234567890123456789012345678901234567890\n2 testControl4\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0");
	testControl4.setDefaultFocusColor(Color_Window_Active_Normal);
	testControl4.isSelectable = true;

	TextBox testTB;
	testTB.setDefaultColor(Color_TextBox_Defocused);
	testTB.setDefaultFocusColor(Color_TextBox_Focused);
	testTB.setCursorColor(Color_TextBox_Cursor);
	testTB.setText("Test Box haha funny :D!");

	Spacer testSpacer;
	testSpacer.setDefaultColor(0);

	middleStack.addControl(&testTB);
	middleStack.addControl(&testSpacer);

	horizStack.addControl(&testControl4);
	horizStack.addControl(&middleStack);
	horizStack.addControl(&testControl2);

	testContainer.addControl(&testControl1);
	testContainer.addControl(&horizStack);
	testContainer.addControl(&testControl3);

	middleStack.draw();
	horizStack.draw();
	testContainer.draw();
	testPrint(&testContainer);

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_RESIZE: testContainer.resize(COLS, LINES); testPrint(&testContainer); break;
			case KEY_F(5): testContainer.setFocus(!testContainer.getFocus()); testPrint(&testContainer); break;
			default: if(isCharNav(ch)) { testContainer.input(ch); testPrint(&testContainer); } break;
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

	testTB.print();

	testSpacer.print();
#endif

	std::exit(0);
}