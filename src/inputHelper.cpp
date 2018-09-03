#include "inputHelper.h"

#include <ncurses.h>

bool isNav(int ch)
{
	bool retVal = false;
	if(ch > 0) switch(ch)
	{
		case '\t':									//Tab
		case '\n':									//Enter
		case 27:									//Escape
		case KEY_DOWN:
		case KEY_UP:
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_BACKSPACE:
		case KEY_ENTER: retVal = true; break;
		default: break;
	}
	return retVal;
}

bool isCharNav(int ch)
{
	return isChar(ch) | isNav(ch);
}