#include "lru.h"
#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

typedef struct lru_node {
    char *key;
    void *item;
    struct lru_node *prev;
    struct lru_node *next;
} lru_node_t;

// Define a structure for the LRU cache
typedef struct lru_cache {
    // Define the maximum capacity of the cache
    int capacity;
    // Keep track of the current size
    int size;
    // A hash table for fast access
    hashtable_t *hash_table;
    lru_node_t *head;
    lru_node_t *tail;
} lru_t;

// Helper functions
static void move_to_front(lru_t *cache, lru_node_t *node) {
    if (node == cache->head) {
        return; // If it is already at the front
    }

    // Remove node from its current position
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }

    // Move to front
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) {
        cache->head->prev = node;
    }
    cache->head = node;

    if (node == cache->tail) {
        cache->tail = node->prev;
    }

    if (!cache->tail) {
        cache->tail = node;
    }
}

static void evict_least_recently_used(lru_t *cache) {
    if (cache == NULL || cache->tail == NULL) {
        return; // No item to evict
    }

    // Retrieve the least recently used node
    lru_node_t *lru_node = cache->tail;
    
    // Update the links in the double-linked list
    if (lru_node->prev) {
        lru_node->prev->next = NULL;
    } else {
        // The list only had one item
        cache->head = NULL;
    }
    cache->tail = lru_node->prev;
    
    // Remove the node from the hash table
    hashtable_remove(cache->hash_table, lru_node->key);

    // Free the node's resources
    free(lru_node->key);
    free(lru_node);

    cache->size--;
}

// Create a new LRU cache
lru_t *lru_new(int capacity) {
    lru_t *cache = malloc(sizeof(lru_t));
    if (!cache) {
        // Handle memory allocation failure
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->hash_table = hashtable_new(capacity); 
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

// Insert an item into the LRU cache
bool lru_insert(lru_t *cache, const char *key, void *item) {
    if (!cache || !key) return false; // Check the arguments to make sure they exist
    
    if (cache->size >= cache->capacity) {
        evict_least_recently_used(cache);
    }

    // Create a new node
    lru_node_t *node = malloc(sizeof(lru_node_t));
    if (node) {
        node->key = strdup(key);
        node->item = item;
        node->prev = NULL;
        node->next = cache->head;
        if (cache->head) {
            cache->head->prev = node;
        }
        cache->head = node;
        if (!cache->tail) {
            cache->tail = node;
        }
    }

    // Insert the item into the hash table
    hashtable_insert(cache->hash_table, key, item);

    cache->size++;

    return true;
}

// Find an item in the LRU cache
void *lru_find(lru_t *cache, const char *key) {
    if (!cache || !key) return NULL;  // Check if the arguments exist

    lru_node_t *node = hashtable_find(cache->hash_table, key);  // Get node
    if (node) {
        move_to_front(cache, node);  // If the node was the found, move it to the front
        return node->item;  // Return item from node
    }
    return NULL;
}

// Print the contents of the LRU cache
void lru_print(lru_t *cache, FILE *fp, void (*itemprint)(FILE *, const char *, void *)) {
    if (!itemprint || !cache) return; // Check arguments

    for (lru_node_t *node = cache->head; node != NULL; node = node->next) {
        itemprint(fp, node->key, node->item);  // Print each item
    }
}

// Iterate over the LRU cache
void lru_iterate(lru_t *cache, void *arg, void (*itemfunc)(void *, const char *, void *)) {
    if (!cache || !itemfunc) return;

    for (lru_node_t *node = cache->head; node != NULL; node = node->next) {
        itemfunc(arg, node->key, node->item);
    }
}

// Delete the LRU cache
void lru_delete(lru_t *cache, void (*itemdelete)(void *item)) {
    if (!cache) return;  // Null check to ensure cache is not NULL
    
    // Clean up resources
    // Iterate through the linked list and free each node
    lru_node_t *current = cache->head;  // Start at the head of the list
    while (current != NULL) {
        lru_node_t *next = current->next;  // Store next node before freeing current
        free(current->key);  // Free the key allocated with strdup
        free(current);       // Free the node itself
        current = next;      // Move to the next node
    }

    hashtable_delete(cache->hash_table, itemdelete);
    free(cache);
}
