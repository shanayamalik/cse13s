#ifndef BAG_HASHTABLE_H            // Include guard to prevent multiple inclusions
#define BAG_HASHTABLE_H

#include <stdio.h>                 // Include the standard I/O library
#include <stdlib.h>                // Include for memory allocation functions
#include <stdbool.h>               // Include for boolean data type
#include <string.h>                // Include for string manipulation functions

#include "crawler.h"               // Include crawler header for webpage_t type

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

// Function prototype to create a new hashtable
hashtable_t *hashtable_create(size_t size);
// Function prototype to insert a key into a hashtable
bool hashtable_insert(hashtable_t *ht, const char *key);
// Function prototype to check if a key is in a hashtable
bool hashtable_lookup(const hashtable_t *ht, const char *key);
// Function prototype to destroy a hashtable and free its resources
void hashtable_destroy(hashtable_t *ht);

#endif // BAG_HASHTABLE_H
