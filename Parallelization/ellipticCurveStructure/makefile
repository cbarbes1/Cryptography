# This file was created by: Cole Barbes on 02/16/23

PROG = Prog
CC = g++
CPPFLAGS = -fopenmp -g -Wall -std=c++11
OBJS =  main.o ellipticCurve.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

ellipticCurve.o : ellipticCurve.h ellipticCurve.cpp ../InfInt.h
	$(CC) $(CPPFLAGS) -c ellipticCurve.cpp

main.o : main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make

