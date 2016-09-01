CC=g++
OBJS=consistent.o hash.o
CFLAGS=-c -Wall -g
LDFLAGS=-g -o

test:$(OBJS)
	$(CC) $(LDFLAGS) $@ $^
%.o:%.cpp
	$(CC) $(CFLAGS) $^

.PHONY:
clean:
	-rm *.o 
cleanall:
	-rm *.o test
