CC=g++
CFLAGS=-Wall -I. -ggdb
LIBS=
SRC=$(wildcard *.cpp) ${wildcard cpp/*.cpp};

program: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clear:
	rm program
