CFLAGS= -g -W -Wall

all: finddupl

clean:
	rm -f *.o finddupl

finddupl: finddupl.o mentry.o mlist.o
	gcc -o finddupl finddupl.o mentry.o mlist.o

finddupl.o: finddupl.c mentry.h mlist.h
mentry.o: mentry.h mentry.c
mlist.o: mlist.c mlist.h mentry.h
