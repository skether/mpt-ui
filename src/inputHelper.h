#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <cctype>

inline bool isChar(int ch) { return ch > 255 || ch < 0 ? false : std::isprint(ch); }

bool isNav(int ch);

bool isCharNav(int ch);

#endif