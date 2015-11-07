CC=gcc

CFLAGS=-Wall -W -g



all: client server

client: client.c
	$(CC) client.c linked_list.c $(CFLAGS) -o client

server: server.c 
	$(CC) server.c linked_list.c $(CFLAGS) -o server

clean:
	rm -f client server *.o

