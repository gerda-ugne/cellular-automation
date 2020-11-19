CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror

all: main.o cellular.o
	$(CC) $(CFLAGS) -o test main.o cellular.o 

main.o: main.c cellular.h
	gcc -c main.c

cellular.o: cellular.c cellular.h
	gcc -c cellular.c