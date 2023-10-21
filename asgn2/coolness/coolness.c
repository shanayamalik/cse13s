#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_usage() {
  printf("Usage: ./coolness [temperature] [wind speed]\n");
  exit(1);
}

void print_error() {
  printf("Error: Coolness. Acceptable input values are -99<=T<=50 and   0.5<=V.\n");
  exit(1);
}

float calculate_coolness(float T, float V) {
  return 35.74 + 0.6215 * T - 35.75 * pow(V, 0.16) + 0.4275 * T * pow(V, 0.16);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // No arguments
    printf("Temp\tWind\tCoolness\n");
    for (float T = -10; T <= 40; T += 10) {
      for (float V = 5; V <= 15; V += 5) {
        float C = calculate_coolness(T, V);
        printf("%5.1f\t%5.1f\t%5.1f\n", T, V, C);
      }
    printf("\n");
    }
  } else if (argc == 2) {
    // One argument
    float T = atof(argv[1]);
    if (T < -99 || T > 50) {
      print_error();
    }
    printf("Temp\tWind\tCoolness\n");
    for (float V = 5; V <= 15; V += 5) {
      float C = calculate_coolness(T, V);
      printf("%5.1f\t%5.1f\t%5.1f\n", T, V, C);
    }
  } else if (argc == 3) {
    // Two arguments
    printf("Temp\tWind\tCoolness\n");
    float T = atof(argv[1]);
    float V = atof(argv[2]);
    if (T < -99 || T > 50 || V < 0.5) {
      print_error();
    }
    float C = calculate_coolness(T, V);
    printf("%5.1f\t%5.1f\t%5.1f\n", T, V, C);
  } else {
    // Invalid number of arguments
    print_usage();
  }
  exit(0);  // Normal exit
}
