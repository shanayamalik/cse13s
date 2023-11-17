#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h" // Include the set header file

// Node structure for the linked list
typedef struct setnode {
    char *key; // Unique key for each item
    void *item; // Pointer to the item data
    struct setnode *next; // Pointer to the next node
} setnode_t;

// Set structure, holding a pointer to the first node
typedef struct set {
    setnode_t *head; // Head of the linked list
} set_t;

// Create a new empty set
set_t* set_new(void) {
    set_t *set = malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL; // Error handling for memory allocation failure
    }
    set->head = NULL; // Initially, the list is empty
    return set;
}

// Insert a new (key, item) pair into the set
bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false; // Check for null pointers
    }

    // Check if the key already exists
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return false; // Key already exists
        }
    }

    // Allocate memory for the new node
    setnode_t *new_node = malloc(sizeof(setnode_t));
    if (new_node == NULL) {
        return false; // Error handling for memory allocation failure
    }

    // Duplicate the key for storage in the node
    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        free(new_node); // Error handling for key duplication failure
        return false;
    }
    new_node->item = item;
    new_node->next = set->head;
    set->head = new_node; // Insert at the beginning of the list

    return true;
}

// Find an item by its key in the set
void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return NULL; // Check for null pointers
    }

    // Iterate through the list to find the key
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            return node->item; // Key found, return the item
        }
    }

    return NULL; // Key not found
}

// Print the entire set
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return; // Check for null file pointer
    }
    if (set == NULL) {
        fprintf(fp, "(null)\n");
        return; // Handle null set
    }
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        if (itemprint != NULL) {
            itemprint(fp, node->key, node->item); // Print each item using the provided function
        }
    }
}

// Iterate over the set and apply a function to each item
void set_iterate(set_t *set, void (*itemfunc)(void *arg, const char *key, void *item), void *arg) {
    if (set == NULL || itemfunc == NULL) {
        return; // Check for null pointers
    }
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
        itemfunc(arg, node->key, node->item); // Apply the function to each item
    }
}

// Delete the whole set
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return; // Ignore NULL set
    }

    // Iterate through the list and free each node
    setnode_t *node = set->head;
    while (node != NULL) {
        setnode_t *next = node->next;

        if (itemdelete != NULL) {
            itemdelete(node->item); // Delete the item using the provided function
        }

        free(node->key); // Free the key string
        free(node); // Free the node
        node = next;
    }

    free(set); // Free the set
}

