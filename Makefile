CC=gcc
CCFLAGS=-I. -g

test: test.o
	$(CC) -o test test.o $(CCFLAGS)
