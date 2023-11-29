#include "hashtable.h"
#include "crawler.h"          // Include crawler header for custom memory functions

// Custom memory allocation functions with error checking
// Redefine the standard allocators to always exit on error to conform with the assignment specification
#define malloc(size)         mem_malloc(size)
#define calloc(num, size)    mem_calloc(num, size)
#define realloc(ptr, size)   mem_realloc(ptr, size)

// Hashtable functions
// A simple hash function for demonstration purposes
unsigned int hash_function(const char *key, unsigned int size) {
    unsigned int hash = 5381;            // Initialize hash value
    int c;
    while ((c = *key++)) {         // Iterate through each character in the string
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % size;            // Return the hash value modulo the hashtable size
}

// Function to create a new hashtable
hashtable_t *hashtable_create(size_t size) {
    hashtable_t *ht = malloc(sizeof(hashtable_t)); // Allocate memory for the hashtable
    ht->table = calloc(size, sizeof(hashtable_node_t *)); // Allocate and zero-initialize array
    ht->size = size;              // Set the size of the hashtable
    return ht;                    // Return the newly created hashtable
}

// Function to insert a key into the hashtable
bool hashtable_insert(hashtable_t *ht, const char *key) {
    unsigned int index = hash_function(key, ht->size); // Calculate the index for the key
    hashtable_node_t *node = ht->table[index]; // Get the first node at the calculated index

    // Check if the key already exists
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return false; // Return false if key already exists
        }
        node = node->next; // Move to the next node
    }

    // Insert new key
    hashtable_node_t *new_node = malloc(sizeof(hashtable_node_t)); // Allocate memory for new node
    new_node->key = strdup(key); // Duplicate the key

    new_node->next = ht->table[index]; // Link the new node to the beginning of the list
    ht->table[index] = new_node;       // Insert the new node at the index
    return true;                       // Return true indicating successful insertion
}

// Function to look up a key in the hashtable
bool hashtable_lookup(const hashtable_t *ht, const char *key) {
    unsigned int index = hash_function(key, ht->size); // Calculate the index for the key
    hashtable_node_t *node = ht->table[index]; // Get the first node at the calculated index

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return true; // Return true if key is found
        }
        node = node->next; // Move to the next node
    }

    return false; // Return false if key is not found
}

// Function to destroy a hashtable and free its resources
void hashtable_destroy(hashtable_t *ht) {
    for (unsigned int i = 0; i < ht->size; i++) { // Iterate over each slot in the table
        hashtable_node_t *node = ht->table[i];
        while (node != NULL) { // Iterate over each node in the list
            hashtable_node_t *temp = node; // Temporary pointer to the current node
            node = node->next;            // Move to the next node
            free(temp->key);              // Free the key of the current node
            free(temp);                   // Free the current node
        }
    }
    free(ht->table); // Free the array of node pointers
    free(ht);        // Free the hashtable structure
}
