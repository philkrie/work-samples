SOURCES = square1.c square2.c diamond.c main.c
HEADERS = square1.h square2.h diamond.h
OBJECTS = $(SOURCES:.c=.o)
LIBS = -lm

CC = gcc
CFLAGS = -std=c99 -g

%.o: %.c
	$(CC) -c $(CFLAGS) $<

main: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

tests: test-square1 test-square2 test-diamond

test-square1: test-square1.o square1.o
	$(CC) -o $@ test-square1.o square1.o $(LIBS)

test-square2: test-square2.o square2.o
	$(CC) -o $@ test-square2.o square2.o $(LIBS)

test-diamond: test-diamond.o diamond.o square2.o
	$(CC) -o $@ test-diamond.o diamond.o square2.o $(LIBS)

test-main: $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIBS)

test-test: test.o square1.o square2.o diamond.o
	$(CC) -o $@ test.o square1.o square2.o diamond.o $(LIBS)

clean: 
	$(RM) main $(OBJECTS)
