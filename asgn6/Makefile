CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
LIBS = -lcurl

# List your .c files here
SRCS = crawler.c pagedir.c hashtable.c bag.c curl.c
OBJS = $(SRCS:.c=.o)

# Name of your executable
PROG = crawler

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Pattern to compile all .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
