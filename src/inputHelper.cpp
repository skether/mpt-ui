#include "inputHelper.h"

bool isNav(int ch)
{
	bool retVal = false;
	switch(ch)
	{
		case KEYCHAR_TAB:
		case KEYCHAR_ENTER:
		case KEYCHAR_ESCAPE:
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