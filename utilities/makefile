# This file was created by: Cole Barbes on 02/16/23

PROG = Prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o functions.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

functions.o : functions.h functions.cpp
	$(CC) $(CPPFLAGS) -c functions.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make

