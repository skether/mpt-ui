CC = g++
CFLAGS = -Wall
CXXFLAGS = -Wall -std=c++11
OUTNAME = mpt-ui

.PHONY: all
all: build
	./$(OUTNAME)

.PHONY: build
build: main.o color.o dimension.o
	$(CC) $(CXXFLAGS) -o $(OUTNAME) $^ -lncurses

.PHONY: clean
clean:
	clear
	rm -f *.o $(OUTNAME)

.PHONY: c
c: clean