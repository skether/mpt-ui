#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

class Control
{
public:
	int width;
	int height;
	int posRow;
	int posCol;
	std::vector<int> contentBuffer;
	std::vector<int> contentColorBuffer;

	Control(int argHeight, int argWidth, int argPosRow, int argPosCol);

	void setColor(int argColor);

private:
	int color;
};

#endif