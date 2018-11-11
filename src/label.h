#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "control.h"

class Label : public Control
{
private:
	std::string text;
	bool wrap;

public:

	Label();

	Label(std::string newText);

	inline std::string getText() { return text; }

	inline void setText(std::string newText) { text = newText; draw(); }

	inline bool getWrap() { return wrap; }

	inline void setWrap(bool newVal) { wrap = newVal; draw(); }

	void draw();

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

#endif