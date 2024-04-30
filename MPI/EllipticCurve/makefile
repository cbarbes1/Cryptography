PROG = mpiprog
CC = mpic++ 
OBJS = ecfactor.o 

$(PROG) : $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

TrialDivisor.o : ecfactor.cpp
	$(CC) $(FLAGS) -c ecfactor.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make
