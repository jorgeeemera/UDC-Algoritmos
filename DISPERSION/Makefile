OBJS	= p3.o dispersion.o
SOURCE	= p3.c dispersion.c
HEADER	= dispersion.h
OUT	= p3
FLAGS	= -g -c -Wall
LFLAGS	= -lm
CC	= gcc

all:	p3

p3: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

p3.o: p3.c
	$(CC) $(FLAGS) p3.c 

dispersion.o: dispersion.c
	$(CC) $(FLAGS) dispersion.c 

clean:
	rm -f $(OBJS) $(OUT)

run: p3
	./p3
