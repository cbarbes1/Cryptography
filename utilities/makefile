# This file was created by: Cole Barbes on 02/16/23

PROG = Prog
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS =  main.o utilities.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

utilities.o : utilities.h utilities.cpp InfInt.h
	$(CC) $(CPPFLAGS) -c utilities.cpp
main.o : main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make

