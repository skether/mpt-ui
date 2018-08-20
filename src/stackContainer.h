#ifndef STACKCONTAINER_H
#define STACKCONTAINER_H

#include "container.h"

class StackContainer : public Container
{
public:
	std::vector<SizingProperty> sizingParameters;

	StackContainer();

	inline void addSizingParameter(SizingProperty val) { sizingParameters.push_back(val); resizeChildren(); }

#ifdef __DEBUG__
	inline void print() { print(true); }

	void print(bool isFirst);
#endif
};

class VerticalStackContainer : public StackContainer
{
public:

	VerticalStackContainer();

	void resizeChildren(int newWidth, int newHeight);
};

class HorizontalStackContainer : public StackContainer
{
public:

	HorizontalStackContainer();

	void resizeChildren(int newWidth, int newHeight);
};

#endif