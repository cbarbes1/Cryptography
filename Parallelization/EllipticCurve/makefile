PROG = mpiprog
CC = mpic++
FLAGS = -fopenmp -g -std=c++11 -Wall -Wextra
OBJS = ecfactor.o ellipticCurve.o

$(PROG) : $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

ellipticCurve.o : ../ellipticCurveStructure/ellipticCurve.h ../ellipticCurveStructure/ellipticCurve.cpp InfInt.h
	$(CC) $(CPPFLAGS) -c ../ellipticCurveStructure/ellipticCurve.cpp

ecfactor.o : ecfactor.cpp
	$(CC) -c ecfactor.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
