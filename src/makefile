CC = g++
CFLAGS = -Wall
CXXFLAGS = -Wall -std=c++11
OUTNAME = mpt-ui


all: main.o color.o window.o control.o
	$(CC) $(CXXFLAGS) -o $(OUTNAME) $^ -lncurses
	./mpt-ui

build: main.o color.o window.o control.o
	$(CC) $(CXXFLAGS) -o $(OUTNAME) $^ -lncurses

.PHONY: clean
clean:
	clear
	rm -f *.o $(OUTNAME)