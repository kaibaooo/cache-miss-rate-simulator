CFLAGS = -std=c++11 -g -Wall
COMPILE = -c
LINK = -o
CC = g++

all:
	$(CC) $(CFLAGS) $(COMPILE) CacheBlock.cpp CacheBlock.h
	$(CC) $(CFLAGS) $(COMPILE) Set_.cpp Set_.h
	$(CC) $(CFLAGS) $(COMPILE) Source.cpp
	$(CC) $(CFLAGS) $(LINK) Source.out *.o
clear:
	rm -rf *.o *.gch