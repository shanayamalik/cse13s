CC = gcc

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

all : histogram 

coolness : histogram.o
	$(CC) -o histogram $(OBJECTS)

%.o : %.c
	$(CC) -c $<

clean:
	rm -f histogram histogram.o
