#include "lru.h"
#include "set.h"
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
} lru_cache_t;

static lru_node_t *create_node(const char *key, void *item) {
    lru_node_t *node = malloc(sizeof(lru_node_t));
    if (node) {
        node->key = strdup(key);
        node->item = item;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

// Helper functions
static void move_to_front(lru_cache_t *cache, lru_node_t *node) {
    if (node == lru->head) {
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
    node->next = lru->head;
    node->prev = NULL;
    if (lru->head) {
        lru->head->prev = node;
    }
    lru->head = node;

    if (node == lru->tail) {
        lru->tail = node->prev;
    }

    if (!lru->tail) {
        lru->tail = node;
    }
}

static void evict_least_recently_used(lru_cache_t *cache) {
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
    hashtable_delete(cache->hash_table, lru_node->key);

    // Free the node's resources
    free(lru_node->key);
    free(lru_node);

    cache->size--;
}

// Create a new LRU cache
lru_cache_t *lru_new(int capacity) {
    lru_cache_t *cache = malloc(sizeof(lru_cache_t));
    if (!cache) {
        // Handle memory allocation failure
        return NULL;
    }

    cache->capacity = capacity;
    cache->size = 0;
    cache->hash_table = hashtable_new(capacity); // Adjust based on hashtable implementation
    cache->order_set = set_new(); // Adjust based on set implementation
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

// Insert an item into the LRU cache
void lru_insert(lru_cache_t *cache, char *key, void *item) {
    if (cache->size >= cache->capacity) {
        evict_least_recently_used(cache);
    }

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

    // Add the item to the front of the order set/linked list
    set_insert_front(cache->order_set, key, item);

    cache->size++;
}

// Find an item in the LRU cache
void *lru_find(lru_cache_t *cache, char *key) {
    void *item = hashtable_find(cache->hash_table, key);
    if (item) {
        // Move the item to the front of the order set/linked list
        move_to_front(cache, key);
    }
    return item;
}

// Delete an item from the LRU cache
void lru_delete(lru_cache_t *cache, char *key) {
    hashtable_delete(cache->hash_table, key);
    set_delete(cache->order_set, key);
    cache->size--;
}

// Print the contents of the LRU cache
void lru_print(lru_cache_t *cache) {
    // Implement based on your set and hashtable ADTs
}

// Iterate over the LRU cache
void lru_iterate(lru_cache_t *cache, void (*itemfunc)(void *arg, const char *key, void *item), void *arg) {
    // Implement based on your set and hashtable ADTs
}

// Delete the LRU cache
void lru_delete(lru_cache_t *cache) {
    // Clean up resources
    hashtable_delete(cache->hash_table);
    set_delete(cache->order_set);
    free(cache);
}
