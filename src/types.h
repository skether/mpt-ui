#ifndef TYPES_H
#define TYPES_H

#include "control.h"

#include <string>

enum class ControlType { Control, Spacer, Label, TextBox, Container, StackContainer, VerticalStackContainer, HorizontalStackContainer};

std::string ControlTypeToString(ControlType t);

class Control;

bool isContainerType(ControlType type);

bool isContainer(Control* cntrl);

#endif