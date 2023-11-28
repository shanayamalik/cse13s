#include "bag_hashtable.h"    // Include the header for bag and hashtable structures
#include "crawler.h"          // Include crawler header for custom memory functions

// Redefine the standard allocators to always exit on error to conform with the assignment specification
#define malloc(x) error_checked_malloc(x)
#define calloc(n, size) error_checked_calloc(n, size)
#define realloc(ptr, size) error_checked_realloc(ptr, size)
#define strdup(s) error_checked_strdup(s)

// Bag functions
// Function to create a new bag
bag_t *bag_new() {
    bag_t *bag = malloc(sizeof(bag_t)); // Allocate memory for the bag
    bag->head = NULL;                   // Initialize the head of the bag to NULL
    return bag;                         // Return the newly created bag
}

// Function to insert a webpage into a bag
void bag_insert(bag_t *bag, webpage_t *page) {
    bag_node_t *new_node = malloc(sizeof(bag_node_t)); // Allocate memory for new node
    new_node->page = page;             // Set the page of the new node
    new_node->next = bag->head;        // Link new node to the current head
    bag->head = new_node;              // Update head to be the new node
}

// Function to extract a webpage from a bag
webpage_t *bag_extract(bag_t *bag) {
    if (bag->head == NULL) {           // Check if the bag is empty
        return NULL;                   // Return NULL if bag is empty
    }
    bag_node_t *node = bag->head;      // Get the head node
    webpage_t *page = node->page;      // Extract webpage from the node
    bag->head = node->next;            // Update head to the next node
    free(node);                        // Free the extracted node
    return page;                       // Return the extracted webpage
}

// Function to destroy a bag and free its resources
void bag_delete(bag_t *bag) {
    while (bag->head != NULL) {        // Iterate through all nodes in the bag
        bag_node_t *next = bag->head->next; // Store the next node
        free(bag->head);               // Free the current head node
        bag->head = next;              // Update head to the next node
    }
    free(bag);                         // Free the bag structure itself
}

// Hashtable functions
// A simple hash function for demonstration purposes
unsigned int simple_hash_function(const char *str, unsigned int size) {
    unsigned int hash = 5381;            // Initialize hash value
    int c;
    while ((c = *str++)) {         // Iterate through each character in the string
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % size;            // Return the hash value modulo the hashtable size
}

// Function to create a new hashtable
hashtable_t *hashtable_new(unsigned int size) {
    hashtable_t *ht = malloc(sizeof(hashtable_t)); // Allocate memory for the hashtable
    ht->table = calloc(size, sizeof(hashtable_node_t *)); // Allocate and zero-initialize array
    ht->size = size;              // Set the size of the hashtable
    return ht;                    // Return the newly created hashtable
}

// Function to insert a key into the hashtable
bool hashtable_insert(hashtable_t *ht, const char *key) {
    unsigned int index = simple_hash_function(key, ht->size); // Calculate the index for the key
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
    unsigned int index = simple_hash_function(key, ht->size); // Calculate the index for the key
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
void hashtable_delete(hashtable_t *ht) {
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

// Define custom memory allocation functions with error checking

// First clear the macros to prevent infinite loops
#undef malloc
#undef calloc
#undef realloc
#undef strdup

void *error_checked_malloc(size_t size) {
    void *ptr = malloc(size);       // Allocate memory using standard malloc
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory error in malloc()\n");
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

void *error_checked_calloc(size_t nmemb, size_t size) {
    void *ptr = calloc(nmemb, size); // Allocate and zero-initialize memory
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory error in calloc()\n");
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

void *error_checked_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size); // Reallocate memory with standard realloc
    if (!new_ptr && size > 0) {     // Check if reallocation failed (except if size is 0)
        fprintf(stderr, "Out of memory error in realloc()\n");
        exit(1);                    // Exit program on memory reallocation failure
    }
    return new_ptr;                 // Return the reallocated memory pointer
}

char *error_checked_strdup(const char *s) {
    char *new_str = strdup(s);      // Duplicate a string using standard strdup
    if (!new_str) {                 // Check if string duplication failed
        fprintf(stderr, "Out of memory error in strdup()\n");
        exit(1);                    // Exit program on string duplication failure
    }
    return new_str;                 // Return the duplicated string
}
