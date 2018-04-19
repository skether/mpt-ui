CC = g++
FLAGS = -Wall

all: clean main.cpp color.c color.h window.cpp window.h control.c control.h
	clear
	$(CC) $(FLAGS) -o mpt-ui main.cpp color.c window.cpp control.cpp -lncurses
	./mpt-ui

clean:
	rm -f *.o mpt-ui