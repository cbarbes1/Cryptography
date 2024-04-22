PROG = mpiprog
CC = mpic++
OBJS = TrialDivisor.o 

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

TrialDivisor.o : TrialDivisor.cpp
	$(CC) -c TrialDivisor.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make