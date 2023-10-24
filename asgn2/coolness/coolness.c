/* Include the header files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Print the usage message and exit the program with error code 1 if more than two arguments are passed */
void print_usage() {
  printf("Usage: ./coolness [temperature] [wind speed]\n");
  exit(1); 
} 

/* Print the usage message and exit the program with error code 1 if either of the arguments are unacceptable */
void print_error() {
  printf("Error: Coolness. Acceptable input values are -99<=T<=50 and   0.5<=V.\n");
  exit(1);
}

/* The formula for calculating coolness is a function of wind speed and temperature */
float calculate_coolness(float T, float V) {
  return 35.74 + 0.6215 * T - 35.75 * pow(V, 0.16) + 0.4275 * T * pow(V, 0.16);
}

/* If no command line arguments are passed, calculate coolness for a range of parameters */
int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Temp\tWind\tCoolness\n");
    for (float T = -10; T <= 40; T += 10) {
      for (float V = 5; V <= 15; V += 5) {
        float C = calculate_coolness(T, V);
        printf("%5.1f\t%5.1f\t%5.1f\n", T, V, C);
      }
    printf("\n");
    }
  } else if (argc == 2) {
    /* If one argument is passed, assume it is a floating point number for temperature, and print a table of calculated coolness values */
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
        /* If two arguments are passed, the first is the temperature and the second is windspeed, assume that both inputs are valid floating point   numbers, and print a single calculated coolness value for those inputs. */
    printf("Temp\tWind\tCoolness\n");
    float T = atof(argv[1]);
    float V = atof(argv[2]);
    if (T < -99 || T > 50 || V < 0.5) {
      print_error();
    }
    float C = calculate_coolness(T, V);
    printf("%5.1f\t%5.1f\t%5.1f\n", T, V, C);
  } else {
    print_usage();
  }
  /* Exit the program with a return code of 0 */
  exit(0);
}
