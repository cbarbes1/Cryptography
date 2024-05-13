PROG = Prog
CC = g++
CPPFLAGS = -fopenmp -g -Wall -std=c++11
OBJS =  genericMultMatrix.o

$(PROG) : $(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

genericMultMatrix.o : genericMultMatrix.cpp
	$(CC) $(CPPFLAGS) -c genericMultMatrix.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
