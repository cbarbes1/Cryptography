PROG = mpiprog
CC = mpic++
OBJS = ecfactor.o utilities.o

$(PROG) : $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

ecfactor.o : ecfactor.cpp
	$(CC) -c ecfactor.cpp

utilities.o : utilities.h utilities.cpp InfInt.h
	$(CC) -c utilities.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
