CC = gcc

SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

all : coolness 

coolness : coolness.o
	$(CC) -o coolness $(OBJECTS) -lm 

%.o : %.c
	$(CC) -c $<

