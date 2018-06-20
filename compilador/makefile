CC=g++
CFLAGS=-Wall -I.
LIBS=`llvm-config --cxxflags --ldflags --libs core`
SRC=$(wildcard *.cpp)

program: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clear:
	rm program
