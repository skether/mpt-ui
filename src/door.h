#include <ncurses.h>

#ifndef DOOR_H
#define DOOR_H

typedef struct DOOR door;

door* initDoor(int argx, int argy, int argz, int argh, int argw);

void addBorder(door* cdoor);

void printDoor(door* cdoor, WINDOW *win);

#endif