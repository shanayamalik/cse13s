#include <stdio.h>                  // Include for standard I/O functions
#include <stdlib.h>                 // Include for standard library functions
#include <string.h>                 // Include for string handling functions
#include <unistd.h>                 // Include for Unix standard functions, like sleep

#include "crawler.h"                // Include the crawler header
#include "curl.h"                   // Include the curl library header
#include "pagedir.h"                // Include the page directory header
#include "url.h"                    // Include the URL processing header
#include "bag_hashtable.h"          // Include the bag and hashtable header

// Custom memory allocation functions with error checking
// Define custom memory allocation functions with error checking
void *mem_malloc(size_t size) {
    void *ptr = malloc(size);       // Allocate memory using standard malloc
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory error on malloc\n");
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

void *mem_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size); // Reallocate memory with standard realloc
    if (!new_ptr && size > 0) {     // Check if reallocation failed (except if size is 0)
        fprintf(stderr, "Out of memory error on realloc\n");
        exit(1);                    // Exit program on memory reallocation failure
    }
    return new_ptr;                 // Return the reallocated memory pointer
}

void *mem_calloc(size_t num, size_t size) {
    void *ptr = calloc(num, size); // Allocate and zero-initialize memory
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory error on calloc\n");
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

char *mem_strdup(const char *s) {
    char *new_str = strdup(s);      // Duplicate a string using standard strdup
    if (!new_str) {                 // Check if string duplication failed
        fprintf(stderr, "Out of memory error on strdup\n");
        exit(1);                    // Exit program on string duplication failure
    }
    return new_str;                 // Return the duplicated string
}

char *mem_strndup(const char *s, size_t n) {
    char *new_str = strndup(s, n);  // Duplicate a string up to n characters
    if (!new_str) {                 // Check if string duplication failed
        fprintf(stderr, "Out of memory error on strndup\n");
        exit(1);                    // Exit program on string duplication failure
    }
    return new_str;                 // Return the duplicated string
}

// Redefine memory and string allocation functions to use those custom versions
#define malloc(size)         mem_malloc(size)
#define realloc(ptr, size)   mem_realloc(ptr, size)
#define calloc(num, size)    mem_calloc(num, size)
#define strdup(s)            mem_strdup(s)
#define strndup(s, n)        mem_strndup(s, n)

// Helper function to remove fragment from URL by modifying the original URL in place
void remove_url_fragment(char *url) {
    char *fragment_pos = strchr(url, '#');  // Find the position of '#' in the URL
    if (fragment_pos) {                     // Check if '#' was found in the URL
        *fragment_pos = '\0';               // Replace '#' with null character to truncate the URL
    }
    // No return needed as the URL is modified in place
}

// Function to parse command-line arguments
void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    if (argc != 4) {   // Check if the number of arguments is exactly 4
        fprintf(stderr, "Usage: crawler seedURL pageDirectory maxDepth\n");
        exit(2);       // Exit if the argument count is incorrect
    }

    *seedURL = strdup(argv[1]);  // Duplicate the seed URL argument
    remove_url_fragment(*seedURL);  // Process the seed URL to remove #fragment in place
    // Check if seed URL starts with 'http://' or 'https://'
    if (!(strncmp(*seedURL, "http://", 7) == 0 || strncmp(*seedURL, "https://", 8) == 0)) {
        fprintf(stderr, "Invalid seed URL. Seed URL must start with http:// or https://\n");
        exit(3);   // Exit if the seed URL is invalid
    }

    *pageDirectory = strdup(argv[2]);  // Duplicate the page directory argument
    *maxDepth = atoi(argv[3]);         // Convert the max depth argument to an integer

    // Check if max depth is within the valid range [0..10]
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "Max depth must be in the range [0..10]\n");
        exit(4);   // Exit if max depth is out of range
    }

    // Initialize the page directory (exits on error)
    pagedir_init(*pageDirectory);
}

// Function to crawl webpages
void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    // Implementation for crawling webpages goes here
    // This includes initializing data structures, downloading pages, and saving them
}

// Main function
int main(const int argc, char *argv[]) {
    char *seedURL, *pageDirectory;                 // Declare pointers for URL and directory
    int maxDepth;                                  // Declare an integer for max depth

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth); // Parse command-line arguments
    crawl(seedURL, pageDirectory, maxDepth);       // Start the crawling process

    free(seedURL);                                 // Free the memory allocated for seedURL
    free(pageDirectory);                           // Free the memory allocated for pageDirectory

    return 0;                                      // Return 0 indicating successful execution
}
