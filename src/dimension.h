#ifndef DIMENSION_H
#define DIMENSION_H

class Size
{
public:
	int height;
	int width;

	Size() : Size(0, 0) {}

	Size(int argWidth, int argHeight);
};

class Position
{
public:
	int x;
	int y;

	Position() : Position(0, 0) {}

	Position(int argX, int argY);
};

class SizingProperty
{
public:
	double value;	//If isPercentage and >=0 then it's a percentage of the original size, if it's <0 then it's a percentage of the remaining size.
	bool isPercentage;

	SizingProperty() : SizingProperty(0, false) {}

	SizingProperty(double argValue) : SizingProperty(argValue, false) {}

	SizingProperty(double argValue, bool argIsPercentage);
};

#endif