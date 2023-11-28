#ifndef CRAWLER_H          // Include guard to prevent multiple inclusions
#define CRAWLER_H

#include <stddef.h>        // Include for general purpose standard library definitions
#include <stdbool.h>       // Include for boolean data type
#include <stdlib.h>        // Include for standard library functions

// Structure definition for a webpage
typedef struct {
    char *url;            // Pointer to a string containing the URL of the webpage
    char *html;           // Pointer to a string containing the HTML content of the webpage
    size_t length;        // Length of the HTML content
    int depth;            // Depth of the webpage in the crawling process
} webpage_t;

// Function prototype for malloc_with_check
void *malloc_with_check(size_t size);   // Custom malloc function with error checking
// Function prototype for realloc_with_check
void *realloc_with_check(void *ptr, size_t size); // Custom realloc function with error checking
// Function prototype for calloc_with_check
void *calloc_with_check(size_t nmemb, size_t size); // Custom calloc function with error checking
// Function prototype for strdup_with_check
char *strdup_with_check(const char *s); // Custom strdup function with error checking
// Function prototype for strndup_with_check
char *strndup_with_check(const char *s, size_t n); // Custom strndup function with error checking

#endif // CRAWLER_H
