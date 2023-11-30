CC = gcc
CFLAGS = -Wall -pedantic -g
LIBS = -lcurl

# List your .c files here
SRCS = crawler.c pagedir.c hashtable.c bag.c curl.c url.c

# Convert the .c files to .o files
OBJS = $(SRCS:.c=.o)

# Name of your executable
PROG = crawler

# Default target
all: $(PROG)

# Link the program
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

# Compile the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependencies for .h files
-include $(SRCS:.c=.d)

# Generate a dependency file for each source file
%.d: %.c
	$(CC) -M $(CFLAGS) $< > $@

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG) *.d
