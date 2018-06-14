CC=g++
CFLAGS=-Wall -I.
LIBS=
SRC=$(wildcard *.cpp)

program: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clear:
	rm program
