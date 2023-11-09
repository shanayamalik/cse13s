# Define compiler
CC=gcc

# Define flags
CFLAGS=-Wall -Wextra -Wpedantic

# Define the target executable
TARGET=growing_arrays

# Define object files
OBJ=growing_arrays.o main.o

# Default target
all: $(TARGET)

# Link the object files into the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the source files into object files
growing_arrays.o: growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

# Clean target for removing compiled files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets
.PHONY: all clean
