#include <stdio.h>                  // Include for standard I/O functions
#include <stdlib.h>                 // Include for standard library functions
#include <string.h>                 // Include for string handling functions
#include <unistd.h>                 // Include for Unix standard functions, like sleep

#include "crawler.h"                // Include the crawler header
#include "curl.h"                   // Include the curl library header
#include "pagedir.h"                // Include the page directory header
#include "url.h"                    // Include the URL processing header
#include "bag_hashtable.h"          // Include the bag and hashtable header

// Custom memory allocation functions with error checking

void *mem_malloc(size_t size) {
    void *ptr = malloc(size);       // Allocate memory using standard malloc
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

void *mem_realloc(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size); // Reallocate memory with standard realloc
    if (!new_ptr && size > 0) {     // Check if reallocation failed (except if size is 0)
        fprintf(stderr, "Out of memory reallocating %zu bytes\n", size);
        exit(1);                    // Exit program on memory reallocation failure
    }
    return new_ptr;                 // Return the reallocated memory pointer
}

void *mem_calloc(size_t nmemb, size_t size) {
    void *ptr = calloc(nmemb, size); // Allocate and zero-initialize memory
    if (!ptr) {                     // Check if memory allocation failed
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);                    // Exit program on memory allocation failure
    }
    return ptr;                     // Return the allocated memory pointer
}

char *mem_strdup(const char *s) {
    char *new_str = strdup(s);      // Duplicate a string using standard strdup
    if (!new_str) {                 // Check if string duplication failed
        fprintf(stderr, "Out of memory duplicating string\n");
        exit(1);                    // Exit program on string duplication failure
    }
    return new_str;                 // Return the duplicated string
}

char *mem_strndup(const char *s, size_t n) {
    char *new_str = strndup(s, n);  // Duplicate a string up to n characters
    if (!new_str) {                 // Check if string duplication failed
        fprintf(stderr, "Out of memory duplicating string\n");
        exit(1);                    // Exit program on string duplication failure
    }
    return new_str;                 // Return the duplicated string
}

// Redefine memory and string allocation functions to use those custom versions
#define malloc(size)         mem_malloc(size)
#define realloc(ptr, size)   mem_realloc(ptr, size)
#define calloc(nmemb, size)  mem_calloc(nmemb, size)
#define strdup(s)            mem_strdup(s)
#define strndup(s, n)        mem_strndup(s, n)

// Helper function to remove fragment from URL by modifying the original URL in place
void remove_url_fragment(char *url) {
    char *fragment_start = strchr(url, '#');  // Find the position of '#' in the URL
    if (fragment_start) {                     // Check if '#' was found in the URL
        *fragment_start = '\0';               // Replace '#' with null character to truncate the URL
    }
    // No return needed as the URL is modified in place
}

// Function to parse command-line arguments
int parse_args(int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    if (argc != 4) {   // Check if the number of arguments is exactly 4
        fprintf(stderr, "Usage: crawler seedURL pageDirectory maxDepth\n");
        exit(2);       // Exit if the argument count is incorrect
    }

    *seedURL = strdup(argv[1]);  // Duplicate the seed URL argument
    remove_url_fragment(*seedURL);  // Process the seed URL to remove #fragment in place
    // Check if seed URL starts with 'http://' or 'https://'
    if (!(strncmp(*seedURL, "http://", 7) == 0 || strncmp(*seedURL, "https://", 8) == 0)) {
        fprintf(stderr, "Invalid URL. The URL must start with either http:// or https://\n");
        exit(3);   // Exit if the seed URL is invalid
    }

    *pageDirectory = strdup(argv[2]);  // Duplicate the page directory argument
    *maxDepth = atoi(argv[3]);         // Convert the max depth argument to an integer

    // Check if max depth is within the valid range [0..10]
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "Max depth must be in the range [0..10]\n");
        exit(4);   // Exit if max depth is out of range
    }

    // Initialize the page directory (exits on error)
    pagedir_init(*pageDirectory);
}

// Function to extract links from HTML content
char **extract_links(const char *html) {
    const char *link_pattern = "<a href=\"";  // Define the pattern to search for
    size_t link_pattern_len = strlen(link_pattern);  // Length of the link pattern
    size_t links_capacity = 10;  // Initial capacity for the array of links
    size_t link_count = 0;       // Counter for the number of links found
    char **links = malloc(links_capacity * sizeof(char *));  // Allocate initial array

    const char *ptr = html;  // Pointer to scan through the HTML content
    while ((ptr = strstr(ptr, link_pattern)) != NULL) {  // Find the link pattern
        ptr += link_pattern_len;  // Move pointer past the link pattern
        const char *end_quote = strchr(ptr, '\"');  // Find the end of the URL
        if (end_quote == NULL) {
            break;  // Break if malformed HTML (missing end quote)
        }

        size_t url_len = end_quote - ptr;  // Calculate the length of the URL
        char *url = strndup(ptr, url_len);  // Duplicate the URL

        // Check if the links array needs to be resized
        if (link_count == links_capacity) {
            links_capacity *= 2;  // Double the capacity
            char **new_links = realloc(links, links_capacity * sizeof(char *));
            links = new_links;  // Update the links array pointer
        }

        links[link_count++] = url;  // Store the URL and increment the count
        ptr = end_quote;  // Move the pointer to the end of the current URL
    }

    // Check and resize the links array to fit one more NULL pointer
    if (link_count == links_capacity) {
        char **new_links = realloc(links, (links_capacity + 1) * sizeof(char *));
        links = new_links;
    }
    links[link_count] = NULL;  // Mark the end of the links array

    return links;  // Return the array of extracted links
}

// Function to scan a webpage for URLs
void scan_page(webpage_t *page, char *pageDirectory, hashtable_t *hashtable) {
    char **links = extract_links(page->html);  // Extract links from the page's HTML
    char *base_url = page->url;                // Store the base URL of the current page

    // Iterate through the extracted links
    for (size_t i = 0; links[i] != NULL; i++) {
        remove_url_fragment(links[i]);        // Delete any #fragment at end
        char *normalized_url = normalizeURL(base_url, links[i]); // Normalize each URL
        if (normalized_url == NULL) {         // Check if URL normalization failed
            continue;                         // Skip non-normalizable URLs
        }
        // Check if the URL is internal to the base URL's domain
        if (isInternalURL(base_url, normalized_url)) {
            // Try to insert the normalized URL into the hashtable
            if (hashtable_insert(hashtable, normalized_url)) {
                webpage_t *new_page = malloc(sizeof(webpage_t)); // Allocate memory for new page
                new_page->url = normalized_url;  // Set the URL of the new page
                new_page->depth = page->depth + 1; // Set the depth of the new page
                new_page->html = NULL;           // Initialize the HTML content to NULL
                bag_insert(pageDirectory, new_page); // Insert the new page into the bag
                printf("Added URL to bag: %s", new_page->url); // Log the added URL
            } else {
                free(normalized_url);            // Free the URL if already seen
            }
        }
        free(links[i]);                          // Free the memory of the current link
    }
    free(links);                                // Free the array of extracted links
}


// Function to crawl webpages
void crawl(char *seedURL, char *pageDirectory, int maxDepth) {
    hashtable_t *hashtable = hashtable_create(200); // Create a hashtable with 200 slots
    bag_t *bag = bag_create();             // Create a bag to store pages to crawl

    webpage_t *seedPage = malloc(sizeof(webpage_t)); // Allocate memory for the seed page
    seedPage->url = strdup(seedURL);                // Duplicate the seed URL
    seedPage->depth = 0;                            // Set the depth of the seed page to 0
    seedPage->html = NULL;                          // Initialize the HTML content to NULL
    bag_insert(bag, seedPage);                      // Insert the seed page into the bag
    hashtable_insert(hashtable, seedURL);           // Insert the seed URL into the hashtable

    int docID = 1;                                  // Initialize document ID counter
    while ((seedPage = bag_extract(bag)) != NULL) { // Extract pages from the bag

        // sleep(1);  // Sleep for polite crawling (uncomment in production)

        char *html = download(seedPage->url, &seedPage->length); // Download the page
        printf("Downloaded page: %s\n", seedPage->url); // Log the fetched page

        if (html) { // Check if the page was successfully downloaded
            seedPage->html = html;                   // Assign the downloaded HTML to the page

            pagedir_save(seedPage, pageDirectory, docID); // Save the page to the directory
            printf("Saved page %d: %s\n", docID++, seedPage->url); // Log the saved page

            if (seedPage->depth < maxDepth) {       // Check if the depth limit is not reached
                scan_page(seedPage, pageDirectory, hashtable); // Scan page for more links
                printf("Scanned page: %s\n", seedPage->url); // Log the scanned page
            }
            free(html);                             // Free the downloaded HTML content
        } else {
            printf("Failed to download non-retrievable URL: %s\n", seedPage->url); // Log skipped URL
        }
        free(seedPage->url);                        // Free the URL of the seed page
        free(seedPage);                             // Free the seed page
    }

    bag_destroy(bag);                              // Destroy the bag and free resources
    hashtable_destroy(hashtable);                   // Destroy the hashtable and free resources
}

// Main function
int main(int argc, char *argv[]) {
    char *seedURL, *pageDirectory;                 // Declare pointers for URL and directory
    int maxDepth;                                  // Declare an integer for max depth

    parse_args(argc, argv, &seedURL, &pageDirectory, &maxDepth); // Parse command-line arguments
    crawl(seedURL, pageDirectory, maxDepth);       // Start the crawling process

    free(seedURL);                                 // Free the memory allocated for seedURL
    free(pageDirectory);                           // Free the memory allocated for pageDirectory

    return 0;                                      // Return 0 indicating successful execution
}
