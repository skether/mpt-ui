#include "textBox.h"

#include "inputHelper.h"

TextBox::TextBox() : Control()
{
	type = ControlType::TextBox;
	cursorColor = -1;
	isSelectable = true;
}

void TextBox::draw()
{
	int color = getFocus() ? getDefaultFocusColor() : getDefaultColor();
	for (int y = 0; y < getSize().height; ++y)
	{
		for(int x = 0; x < getSize().width; ++x)
		{
			if(y == 0)
			{
				if(isActive)
				{
					if(x < signed(editedText.length())) setCharacter(x, y, editedText[x]);
					else setCharacter(x, y, 32);

					if(x == cursor) setColor(x, y, cursorColor);
					else setColor(x, y, color);
				}
				else
				{
					if(x < signed(text.length())) setCharacter(x, y, text[x]);
					else setCharacter(x, y, 32);

					setColor(x, y, color);
				}
			}
			else
			{
				setCharacter(x, y, 32);
				setColor(x, y, color);
			}
		}
	}

	notifyParent();
}

bool TextBox::input(int ch)
{
	bool retVal = false;
	if(isActive)
	{
		if(isEnter(ch))
		{
			text = editedText;
			isActive = false;
		}
		else if(isEscape(ch))
		{
			editedText = text;
			isActive = false;
		}
		else if(isBackspace(ch))
		{
			if(editedText.length() != 0) editedText.pop_back();
			if(cursor > 0) cursor--;
		}
		else if(isChar(ch))
		{
			editedText.push_back(ch);
			cursor++;
		}

		retVal = true;
	}
	else
	{
		if(isEnter(ch))
		{
			editedText = text;
			cursor = editedText.length();
			isActive = true;
			retVal = true;
		}
	}

	draw();
	return retVal;
}

#ifdef __DEBUG__
#include <iostream>
void TextBox::print(bool isFirst)
{
	if(isFirst) std::cout << ControlTypeToString(type) << "\n";
	std::cout << "\tText:\t\t" << text << "\n";
	std::cout << "\tEdited Text:\t" << editedText << "\n";
	std::cout << "\tCursor:\t\t" << cursor << "\n";
	std::cout << "\tisActive:\t" << isActive << "\n";
	Control::print(false);
}
#endif