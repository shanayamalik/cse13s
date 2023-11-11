CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
OBJ1=growing_arrays.o
OBJ2=test_growing_arrays.o
PARAM ?= growing_arrays

all:
	@if [ "$(PARAM)" = "test_growing_arrays" ]; then \
		$(MAKE) test_growing_arrays; \
	else \
		$(MAKE) growing_arrays; \
	fi

growing_arrays: growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -o $@ growing_arrays.c


test_growing_arrays: test_growing_arrays.c growing_arrays.h
	$(CC) $(CFLAGS) -o $@ test_growing_arrays.c


clean:
	rm -f $(TARGET) $(OBJ)
