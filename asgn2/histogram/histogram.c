/* Include the header file for the stander input-output */
#include <stdio.h>

/* Define the macro BINS with a value of sixteen */
#define BINS 16

/* Declare the array, bins, and initialize all the elements to size zero. The size of each bin should begin at the value of one */
int main() {
  int bins[BINS] = {0};
  int bin_size = 1;
  int max_val = bin_size * BINS;
  int value;

/* Read integers from the standard input until the end of the file has been reached. The smallest integer is assumed to be 0, and if any value is negative, that integer will be ignored. */
  while (scanf("%d", &value) != EOF) {
    if (value < 0) {
        continue;
    }

/* If a value is outside of the range, compress the current sixteen bins into half, which is eight bins, and double the bin size and range. */
    while (value >= max_val) {
      bin_size *= 2;
      max_val = bin_size * BINS;

      for (int i = 0; i < 8; i++) {
        bins[i] = bins[2*i] + bins[2*i + 1];
      }

/* For the upper half of the bins, assign a value of zero to it for calculation */
      for (int i = 8; i < BINS; i++) {
        bins[i] = 0;
      }
    }

    int bin_index = value / bin_size;
    bins[bin_index] += 1;
  }

/*The outer loop iterates over each bin, and the inner loop prints asterisks based on the count in each bin, forming a histogram. */
  for (int i = 0; i < BINS; i++) {
    printf("[%3d:%3d] ", i*bin_size, (i+1)*bin_size-1);
    for (int j = 0; j < bins[i]; j++) {
      printf("*");
    }
    printf("\n");
  }

/* Exit the program with a return code of zero to represent successful execution */
  return 0;
}
