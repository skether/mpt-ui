#ifndef DIMENSION_H
#define DIMENSION_H

class Size
{
public:
	int height;
	int width;

	Size(int argWidth, int argHeight);
};

class Position
{
public:
	int x;
	int y;

	Position(int argX, int argY);
};

#endif