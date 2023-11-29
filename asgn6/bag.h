#ifndef BAG_H            // Include guard to prevent multiple inclusions
#define BAG_H

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

#endif //BAG_H
