CC = g++
FLAGS = -Wall

all: clean main.cpp color.c color.h
	clear
	$(CC) $(FLAGS) -o mpt-ui main.cpp color.c -lncurses
	./mpt-ui

clean:
	rm -f *.o mpt-ui