#include "bag_hashtable.h"    // Include the header for bag and hashtable structures
#include "crawler.h"          // Include crawler header for custom memory functions

// Custom memory allocation functions with error checking are prototyped in bag_hashtable.h and defined below
// Redefine the standard allocators to always exit on error to conform with the assignment specification
#define malloc(size)         mem_malloc(size)
#define calloc(num, size)    mem_calloc(num, size)
#define realloc(ptr, size)   mem_realloc(ptr, size)
#define free(ptr)            mem_free(ptr)

// Bag functions
// Function to create a new bag
bag_t *bag_new() {
    bag_t *bag = malloc(sizeof(bag_t)); // Allocate memory for the bag
    bag->head = NULL;                   // Initialize the head of the bag to NULL
    return bag;                         // Return the newly created bag
}

// Function to insert a webpage into a bag
void bag_insert(bag_t *bag, webpage_t *page) {
    bag_node_t *bag_node = malloc(sizeof(bag_node_t)); // Allocate memory for new node
    bag_node->page = page;             // Set the page of the new node
    bag_node->next = bag->head;        // Link new node to the current head
    bag->head = bag_node;              // Update head to be the new node
}

// Function to extract a webpage from a bag
webpage_t *bag_extract(bag_t *bag) {
    if (bag->head == NULL) {           // Check if the bag is empty
        return NULL;                   // Return NULL if bag is empty
    }
    bag_node_t *temp = bag->head;      // Get the head node
    webpage_t *page = temp->page;      // Extract webpage from the node
    bag->head = temp->next;            // Update head to the next node
    free(temp);                        // Free the extracted node
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
