#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <ncurses.h>

#include "globalDefine.h"

#include "dimension.h"
#include "types.h"

enum class ControlType;

class Control
{
private:
	Position position;
	Size size;

	int defaultColor;
	int defaultFocusColor;

	bool isFocused;

	std::vector<int> characterMap;
	std::vector<int> colorMap;

public:
	bool isSelectable;

	ControlType type;

	Control* parent;

	Control();

	//Matrix indexes to Vector Index
	inline int M2V(int argX, int argY) { return argY * size.width + argX; }

	inline Position getPosition() { return position; }

	inline void setPosition(Position newPos) { position = newPos; }

	inline void setPosition(int newX, int newY) { position.x = newX; position.y = newY; }

	inline Size getSize() { return size; }

	inline int getCharacter(int argX, int argY) { return characterMap[M2V(argX, argY)]; }

	inline void setCharacter(int argX, int argY, int newChar) { characterMap[M2V(argX, argY)] = newChar; }

	inline int getColor(int argX, int argY) { return colorMap[M2V(argX, argY)]; }

	inline void setColor(int argX, int argY, int newColor) { colorMap[M2V(argX, argY)] = newColor; }

	inline int getDefaultColor() { return defaultColor; }

	inline void setDefaultColor(int newColor) { defaultColor = COLOR_PAIR(newColor); if(!isFocused) { draw(); } }

	inline int getDefaultFocusColor() { return defaultFocusColor; }

	inline void setDefaultFocusColor(int newColor) { defaultFocusColor = COLOR_PAIR(newColor); if(isFocused) { draw(); } }

	inline bool getFocus() { return isFocused; }

	inline void setFocus(bool newFocus) { if(newFocus != isFocused) { isFocused = newFocus; draw(); } }

	inline int getCharacterForPrinting(int argX, int argY) { return characterMap[M2V(argX, argY)] | colorMap[M2V(argX, argY)]; }

	virtual void resize(int argW, int argH);

	virtual void draw() = 0;

	inline void notifyParent() { if(parent != 0) { (*parent).draw(); } }

	virtual bool input(int ch);

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

#endif