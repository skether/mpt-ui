#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

#include "globalDefine.h"

#include "dimension.h"

class Control
{
private:
	Position position;
	Size size;

	int defaultColor;

	std::vector<int> characterMap;
	std::vector<int> colorMap;

public:
	Control* parent;

	Control();

	//Matrix indexes to Vector Index
	inline int M2V(int argX, int argY) { return argY * size.width + argX; }

	inline Position getPosition() { return position; }

	inline Size getSize() { return size; }

	inline int getCharacter(int argX, int argY) { return characterMap[M2V(argX, argY)]; }

	inline void setCharacter(int argX, int argY, int newChar) { characterMap[M2V(argX, argY)] = newChar; }

	inline int getColor(int argX, int argY) { return colorMap[M2V(argX, argY)]; }

	inline void setColor(int argX, int argY, int newColor) { colorMap[M2V(argX, argY)] = newColor; }

	inline int getDefaultColor() { return defaultColor; }

	inline void setDefaultColor(int newColor) { defaultColor = newColor; colorMap.clear(); colorMap.resize(size.width * size.height, defaultColor); }

	void resize(int argW, int argH);

	virtual void draw() = 0;

#ifdef __DEBUG__
	void print();
#endif
};

#endif