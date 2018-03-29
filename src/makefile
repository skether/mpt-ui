CC = gcc
FLAGS = -Wall -std=c99

all: clean mpt-ui.c door.c door.h colornames.h
	clear
	$(CC) $(FLAGS) -o mpt-ui mpt-ui.c door.c -lcurses
	./mpt-ui

clean:
	rm -f *.o mpt-ui