CC = gcc
FLAGS = -Wall -std=c99

all: mpt-ui.c clean
	clear
	$(CC) $(FLAGS) -o mpt-ui mpt-ui.c -lcurses
	./mpt-ui

clean:
	rm -f *.o mpt-ui