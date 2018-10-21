#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>

#include "control.h"

class TextBox : public Control
{
private:
	std::string text;
	std::string editedText;
	bool isActive;
	int cursor;

	int cursorColor;

public:

	TextBox();

	inline std::string getText() { return text; }

	inline void setText(std::string newText) { text = newText; cursor = text.length(); draw(); }

	inline int getCursorColor() { return cursorColor; }

	inline void setCursorColor(int newColor) { cursorColor = COLOR_PAIR(newColor); if(isActive) { draw(); } }

	virtual void draw();

	virtual bool input(int ch);

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

#endif