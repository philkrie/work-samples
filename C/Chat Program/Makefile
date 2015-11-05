CC=gcc -std=c99

CFLAGS=-Wall -W -g -Werror



all: client server

client: client.c raw.c
	$(CC) client.c linked_list.c raw.c $(CFLAGS) -o client

server: server.c 
	$(CC) server.c linked_list.c $(CFLAGS) -o server

clean:
	rm -f client server *.o

