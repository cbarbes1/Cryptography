PROG = mpiprog
CC = mpic++
OBJS = helloworld.o 

$(PROG) : $(OBJS)
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)

helloworld.o : helloworld.cpp
	$(CC) $(FLAGS) -c helloworld.cpp

clean:
	rm -f core $(PROG) $(OBJS)

rebuild:
	make clean
	make