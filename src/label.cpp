#include "label.h"

Label::Label() : Control()
{
	type = ControlType::Label;
	wrap = false;
}

void Label::draw()
{
	unsigned int cI = 0;
	bool newLine;
	bool wordStart = true;
	int color = getFocus() ? getDefaultFocusColor() : getDefaultColor();
	for (int y = 0; y < getSize().height; ++y)
	{
		newLine = false;
		if(text[cI] == ' ') while(cI < text.length() && text[cI] == ' ') cI++;
		for (int x = 0; x < getSize().width; ++x)
		{
			if(newLine) setCharacter(x, y, 32);
			else
			{
				if(cI < text.length())
				{
					if(text[cI] == '\n')
					{
						newLine = true;
						wordStart = true;
						setCharacter(x, y, 32);
					}
					else
					{
						if(wrap)
						{
							if(wordStart)
							{
								if(text[cI] == ' ') setCharacter(x, y, ' ');
								else
								{
									wordStart = false;

									unsigned int wI = cI;
									while(wI < text.length() && text[wI] != ' ' && text[wI] != '\n') wI++;
									if(wI == text.length()) wI--;

									if(unsigned(getSize().width - x) < (wI - cI) && x != 0) newLine = true;

									if(newLine)
									{
										cI--;
										setCharacter(x, y, ' ');
									} 
									else setCharacter(x, y, text[cI]);
								}
							}
							else
							{
								if(text[cI] == ' ') wordStart = true;
								setCharacter(x, y, text[cI]);
							}
						}
						else setCharacter(x, y, text[cI]);
						cI++;
					}
				}
				else setCharacter(x, y, 32);
			}

			setColor(x, y, color);
		}
		if(!wrap && !newLine) while(cI < text.length() && text[cI] != '\n') cI++;
		if(text[cI] == '\n') cI++;
	}

	notifyParent();
}

#ifdef __DEBUG__
#include <iostream>
void Label::print(bool isFirst)
{
	if(isFirst) std::cout << ControlTypeToString(type) << "\n";
	std::cout << "\tText:\t\t" << text << "\n";
	std::cout << "\tWrap:\t\t" << wrap << "\n";
	Control::print(false);
}
#endif