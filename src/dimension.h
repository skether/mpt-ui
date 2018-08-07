#ifndef DIMENSION_H
#define DIMENSION_H

class Size
{
public:
	int height;
	int width;

	Size():Size(0, 0){}

	Size(int argWidth, int argHeight);
};

class Position
{
public:
	int x;
	int y;

	Position():Position(0, 0){}

	Position(int argX, int argY);
};

#endif