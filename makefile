all: myapp

# Which compiler
CC = gcc

# Where are include files kept
INCLUDE = .

# Options for development
CFLAGS = -g -Wall -ansi

# Options for release
# CFLAGS = -O -Wall -ansi -lrt

# Linux Program chapter03. File operation.
L6_FILES = main601.o main602.o main603.o main801.o main1001.o

myapp: main.o \
	$(L6_FILES)
	$(CC) -o myapp main.o $(L6_FILES)

main.o: main.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.c

# Linux Program chapter06. 
main601.o: main601.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main601.c
main602.o: main602.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main602.c
main603.o: main603.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main603.c	
main801.o: main801.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main801.c	
main1001.o: main1001.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main1001.c

