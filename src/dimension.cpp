#include "dimension.h"

Size::Size(int argWidth, int argHeight)
{
	width = argWidth;
	height = argHeight;
}

Position::Position(int argX, int argY)
{
	x = argX;
	y = argY;
}

SizingProperty::SizingProperty(double argValue, bool argIsPercentage)
{
	value = argValue;
	isPercentage = argIsPercentage;
}