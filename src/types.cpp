#include "types.h"

std::string ControlTypeToString(ControlType t)
{
	switch(t)
	{
		case ControlType::Control: return "Control";
		case ControlType::Spacer: return "Spacer";
		case ControlType::Label: return "Label";
		case ControlType::TextBox: return "TextBox";
		case ControlType::Container: return "Container";
		case ControlType::StackContainer: return "StackContainer";
		case ControlType::VerticalStackContainer: return "VerticalStackContainer";
		case ControlType::HorizontalStackContainer: return "HorizontalStackContainer";
		default: return "No such type!";
	}
}

bool isContainerType(ControlType type)
{
	bool returnValue = false;
	switch(type)
	{
		case ControlType::Container:
		case ControlType::StackContainer:
		case ControlType::VerticalStackContainer:
		case ControlType::HorizontalStackContainer: returnValue = true; break;
		default: returnValue = false; break;
	}
	return returnValue;
}

bool isContainer(Control* cntrl)
{
	return isContainerType((*cntrl).type);
}