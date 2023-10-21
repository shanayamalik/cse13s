#include <stdio.h>

#define BINS 16

int main() {
  int bins[BINS] = {0};
  int bin_size = 1;
  int max_val = bin_size * BINS;
  int value;

  while (scanf("%d", &value) != EOF) {
    // Ignore negative values
    if (value < 0) {
        continue;
    }

    // Check if we need to adjust bins
    while (value >= max_val) {
      // Double the bin size
      bin_size *= 2;
      max_val = bin_size * BINS;

      // Compress the current bins into the first half
      for (int i = 0; i < 8; i++) {
        bins[i] = bins[2*i] + bins[2*i + 1];
      }

      // Reset the upper half of the bins to zero
      for (int i = 8; i < BINS; i++) {
        bins[i] = 0;
      }
    }

    // Increment the correct bin
    int bin_index = value / bin_size;
    bins[bin_index] += 1;
  }

  // Print the histogram
  for (int i = 0; i < BINS; i++) {
    printf("[%3d:%3d] ", i*bin_size, (i+1)*bin_size-1);
    for (int j = 0; j < bins[i]; j++) {
      printf("*");
    }
    printf("\n");
  }

  return 0;
}
