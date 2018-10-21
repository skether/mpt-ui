#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <cctype>
#include <ncurses.h>

#define KEYCHAR_ENTER 10
#define KEYCHAR_TAB 9
#define KEYCHAR_ESCAPE 27

inline bool isChar(int ch) { return ch > 255 || ch < 0 ? false : std::isprint(ch); }

inline bool isEnter(int ch) { return ch == KEY_ENTER || ch == KEYCHAR_ENTER; }

inline bool isTab(int ch) { return ch == KEYCHAR_TAB; }

inline bool isEscape(int ch) { return ch == KEYCHAR_ESCAPE; }

inline bool isBackspace(int ch) { return ch == KEY_BACKSPACE; }

bool isNav(int ch);

bool isCharNav(int ch);

#endif