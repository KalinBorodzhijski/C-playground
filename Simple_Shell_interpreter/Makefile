CC=gcc
CFLAGS=-Wall -g

all: shell

shell: shell.o command.o utils.o
	$(CC) $(CFLAGS) -o shell shell.o command.o utils.o

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o shell
