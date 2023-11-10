CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
TARGET=growing_arrays
OBJ=growing_arrays.o test_growing_arrays.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

growing_arrays.o: growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

test_growing_arrays.o: test_growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJ)
