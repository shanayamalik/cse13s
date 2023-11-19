#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "set.h"

typedef struct hashtable {
    int slots;
    set_t **table;
} hashtable_t;

// Basic hash function for strings
static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;

    // Iteratively calculate the hash for each character in the string
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

// Create a new (empty) hashtable
hashtable_t *hashtable_new(const int slots) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Allocate memory for the array of set pointers
    ht->slots = slots;
    ht->table = malloc(sizeof(set_t *) * slots);
    if (ht->table == NULL) {
        free(ht); // Free previously allocated memory
        return NULL;
    }

    ht->slots = slots;
    // Initialize each set in the array
    for (int i = 0; i < slots; i++) {
        ht->table[i] = set_new();
        if (ht->table[i] == NULL) {
            // Cleanup in case of failure
            for (int j = 0; j < i; j++) {
                set_delete(ht->table[j], NULL);
            }
            free(ht->table);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

// Insert item into the hashtable
bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false; // Return false if any parameter is NULL
    }

    // Calculate hash and determine the appropriate slot
    unsigned long hash = hash_string(key);
    int slot = hash % ht->slots;

    // Check if key already exists in the set
    if (set_find(ht->table[slot], key) != NULL) {
        return false;
    }

    // Insert new item into the set
    return set_insert(ht->table[slot], key, item);
}

// Find item by key in the hashtable
void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL; // Return NULL if hashtable or key is NULL
    }

    // Calculate hash and determine the appropriate slot
    unsigned long hash = hash_string(key);
    int slot = hash % ht->slots;

    // Find and return the item from the set
    return set_find(ht->table[slot], key);
}

// Print the hashtable
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL || fp == NULL || itemprint == NULL) {
        return; // Do nothing if any parameter is NULL
    }

    // Iterate over each slot and print its contents
    for (int i = 0; i < ht->slots; i++) {
        set_t *slot = ht->table[i];
        set_print(slot, fp, itemprint);
    }
}

// Iterate over all items in the hashtable
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return; // Do nothing if hashtable or function pointer is NULL
    }

    // Iterate over each slot and apply the function to its items
    for (int i = 0; i < ht->slots; i++) {
        set_t *slot = ht->table[i];
        set_iterate(slot, arg, itemfunc);
    }
}

void hashtable_remove(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return;
    }

    int index = hash_function(key, ht->slots);
    // Assuming set_remove is a function that removes a key-item pair from the set
    set_remove(ht->table[index], key);
}

    free(ht->table);
    free(ht);
}

