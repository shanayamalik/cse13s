# Define compiler
CC=gcc

# Define flags
CFLAGS=-Wall -Wextra -Wpedantic

# Define the target executable
TARGET=check_cycle

# Define object files
OBJ=ll_cycle.o test_ll_cycle.o

# Default target
all: $(TARGET)

# Link the object files into the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the source files into object files
ll_cycle.o: ll_cycle.c ll_cycle.h
	$(CC) $(CFLAGS) -c $<

test_ll_cycle.o: test_ll_cycle.c ll_cycle.h
	$(CC) $(CFLAGS) -c $<

# Clean target for removing compiled files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets
.PHONY: all clean
