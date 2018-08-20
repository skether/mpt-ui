#include "stackContainer.h"

#include <cmath>

StackContainer::StackContainer() : Container() {}

VerticalStackContainer::VerticalStackContainer() : StackContainer() {}

void VerticalStackContainer::resizeChildren(int newWidth, int newHeight)
{
	std::vector<int> calculatedSizeValues;
	calculatedSizeValues.resize(sizingParameters.size() < controls.size() ? sizingParameters.size() : controls.size(), 0);

	int spaceRemaining = newHeight;
	double totalRelativeUnits = 0;
	for (unsigned int i = 0; i < calculatedSizeValues.size(); ++i)
	{
		if(sizingParameters[i].isPercentage)
		{
			if(sizingParameters[i].value < 0)
			{
				calculatedSizeValues[i] = -1;
				totalRelativeUnits -= sizingParameters[i].value;
			}
			else
			{
				spaceRemaining -= calculatedSizeValues[i] = std::floor(newHeight * sizingParameters[i].value);
			}

		}
		else
		{
			spaceRemaining -= calculatedSizeValues[i] = sizingParameters[i].value < 0 ? 0 : std::floor(sizingParameters[i].value);
		}
	}

	if(totalRelativeUnits > 0)
	{
		if(spaceRemaining < 0) spaceRemaining = 0;

		int lastRelativeIndex = -1;
		int spaceRemainingBeforeRelative = spaceRemaining;
		for (unsigned int i = 0; i < calculatedSizeValues.size(); ++i)
		{
			if(calculatedSizeValues[i] == -1)
			{
				spaceRemaining -= calculatedSizeValues[i] = std::floor((std::abs(sizingParameters[i].value) / totalRelativeUnits) * spaceRemainingBeforeRelative);
				lastRelativeIndex = i;
			}
		}
		if(spaceRemaining > 0) calculatedSizeValues[lastRelativeIndex] += spaceRemaining;
	}

	for (unsigned int i = 0; i < controls.size(); ++i)
	{
		if(i < calculatedSizeValues.size())
		{
			if(i == 0)
			{
				(*controls[i]).setPosition(0, 0);
				(*controls[i]).resize(newWidth, calculatedSizeValues[i]);
			}
			else
			{
				(*controls[i]).setPosition(0, ((*controls[i-1]).getPosition().y + (*controls[i-1]).getSize().height));
				(*controls[i]).resize(newWidth, calculatedSizeValues[i]);
			}
		}
		else
		{
			(*controls[i]).setPosition(0, newHeight);
			(*controls[i]).resize(0, 0);
		}
	}
}

HorizontalStackContainer::HorizontalStackContainer() : StackContainer() {}

void HorizontalStackContainer::resizeChildren(int newWidth, int newHeight)
{
	std::vector<int> calculatedSizeValues;
	calculatedSizeValues.resize(sizingParameters.size() < controls.size() ? sizingParameters.size() : controls.size(), 0);

	int spaceRemaining = newWidth;
	double totalRelativeUnits = 0;
	for (unsigned int i = 0; i < calculatedSizeValues.size(); ++i)
	{
		if(sizingParameters[i].isPercentage)
		{
			if(sizingParameters[i].value < 0)
			{
				calculatedSizeValues[i] = -1;
				totalRelativeUnits -= sizingParameters[i].value;
			}
			else
			{
				spaceRemaining -= calculatedSizeValues[i] = std::floor(newWidth * sizingParameters[i].value);
			}

		}
		else
		{
			spaceRemaining -= calculatedSizeValues[i] = sizingParameters[i].value < 0 ? 0 : std::floor(sizingParameters[i].value);
		}
	}

	if(totalRelativeUnits > 0)
	{
		if(spaceRemaining < 0) spaceRemaining = 0;

		int lastRelativeIndex = -1;
		int spaceRemainingBeforeRelative = spaceRemaining;
		for (unsigned int i = 0; i < calculatedSizeValues.size(); ++i)
		{
			if(calculatedSizeValues[i] == -1)
			{
				spaceRemaining -= calculatedSizeValues[i] = std::floor((std::abs(sizingParameters[i].value) / totalRelativeUnits) * spaceRemainingBeforeRelative);
				lastRelativeIndex = i;
			}
		}
		if(spaceRemaining > 0) calculatedSizeValues[lastRelativeIndex] += spaceRemaining;
	}

	for (unsigned int i = 0; i < controls.size(); ++i)
	{
		if(i < calculatedSizeValues.size())
		{
			if(i == 0)
			{
				(*controls[i]).setPosition(0, 0);
				(*controls[i]).resize(calculatedSizeValues[i], newHeight);
			}
			else
			{
				(*controls[i]).setPosition(((*controls[i-1]).getPosition().x + (*controls[i-1]).getSize().width), 0);
				(*controls[i]).resize(calculatedSizeValues[i], newHeight);
			}
		}
		else
		{
			(*controls[i]).setPosition(0, newHeight);
			(*controls[i]).resize(0, 0);
		}
	}
}

#ifdef __DEBUG__
#include <iostream>
void StackContainer::print(bool isFirst)
{
	if(isFirst) std::cout << "StackContainer:\n";
	std::cout << "\tSizingParameters:\tsize(" << sizingParameters.size() << "), capacity(" << sizingParameters.capacity() << ")\n";
	Container::print(false);
}
#endif