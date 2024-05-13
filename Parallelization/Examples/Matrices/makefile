PROG = Prog
CC = g++
CPPFLAGS = -fopenmp -g -Wall -std=c++11
OBJS =  dotProductExample.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

dotProductExample.o : dotProductExample.cpp
	$(CC) $(CPPFLAGS) -c dotProductExample.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
