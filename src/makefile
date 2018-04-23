CC = g++
CFLAGS = -Wall
CXXFLAGS = -Wall
OUTNAME = mpt-ui


all: main.o color.o windows.o controls.o
	$(CXX) $(CFLAGS) -o $(OUTNAME) $^ -lncurses
	./mpt-ui

.PHONY: clean
clean:
	clear
	rm -f *.o $(OUTNAME)