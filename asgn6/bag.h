#ifndef BAG_HASHTABLE_H            // Include guard to prevent multiple inclusions
#define BAG_HASHTABLE_H

#include <stdio.h>                 // Include the standard I/O library
#include <stdlib.h>                // Include for memory allocation functions
#include <stdbool.h>               // Include for boolean data type
#include <string.h>                // Include for string manipulation functions

#include "crawler.h"               // Include crawler header for webpage_t type

// Structure for a node in the bag linked list
typedef struct bag_node {
    webpage_t *page;               // Pointer to a webpage_t, stored in the bag
    struct bag_node *next;         // Pointer to the next node in the bag
} bag_node_t;

// Structure representing a bag (a simple stack)
typedef struct {
    bag_node_t *head;              // Pointer to the top node in the bag
} bag_t;

// Structure for a node in the hashtable
typedef struct hashtable_node {
    char *key;                     // Pointer to the key string in the hashtable
    struct hashtable_node *next;   // Pointer to the next node in the hashtable
} hashtable_node_t;

// Structure representing a hashtable
typedef struct {
    hashtable_node_t **table;      // Pointer to an array of pointers to hashtable nodes
    size_t size;                   // Size of the hashtable (number of slots)
} hashtable_t;

// Function prototype to create a new bag
bag_t *bag_create();
// Function prototype to insert a page into a bag
void bag_insert(bag_t *bag, webpage_t *page);
// Function prototype to extract a page from a bag
webpage_t *bag_extract(bag_t *bag);
// Function prototype to destroy a bag and free its resources
void bag_destroy(bag_t *bag);

// Function prototype to create a new hashtable
hashtable_t *hashtable_create(size_t size);
// Function prototype to insert a key into a hashtable
bool hashtable_insert(hashtable_t *ht, const char *key);
// Function prototype to check if a key is in a hashtable
bool hashtable_lookup(const hashtable_t *ht, const char *key);
// Function prototype to destroy a hashtable and free its resources
void hashtable_destroy(hashtable_t *ht);

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

#endif // BAG_HASHTABLE_H
