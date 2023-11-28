#include <stdio.h>
#include <stdlib.h>

#include "crawler.h"
#include "curl.h"

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    // Check if the number of arguments is exactly 4
    if (argc != 4) {
        fprintf(stderr, "Usage: crawler seedURL pageDirectory maxDepth\n");
        exit(1); // Exit if the argument count is incorrect
    }

    // Allocate memory and copy the seed URL argument
    *seedURL = strdup(argv[1]);
    // Check if seed URL starts with 'http://' or 'https://'
    if (!(strncmp(*seedURL, "http://", 7) == 0 || strncmp(*seedURL, "https://", 8) == 0)) {
        fprintf(stderr, "Invalid seed URL. It must start with either http:// or https://\n");
        exit(2); // Exit if the seed URL is invalid
    }

    // Allocate memory and copy the page directory argument
    *pageDirectory = strdup(argv[2]);

    // Convert the max depth argument to an integer
    *maxDepth = atoi(argv[3]);
    // Check if max depth is within the valid range [0..10]
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "Max depth must be in range [0..10]\n");
        exit(3); // Exit if max depth is out of range
    }
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    hashtable_t *pages_seen = hashtable_new(200);  // Create a hashtable
    bag_t *pages_to_crawl = bag_new();            // Create a bag

    // Create the initial webpage and add it to the bag and hashtable
    webpage_t *initial_page = webpage_new(seedURL, 0, NULL);
    bag_insert(pages_to_crawl, initial_page);
    hashtable_insert(pages_seen, seedURL);

    int doc_id = 1; // Document ID for saved pages

    // Continue crawling as long as there are pages in the bag
    while ((initial_page = bag_extract(pages_to_crawl)) != NULL) {
        char *page_content = NULL;

        sleep(1); // Polite crawling
        fetch_page(initial_page->url, &page_content); // Fetch the page content

        if (page_content != NULL) {
            pagedir_save(initial_page, pageDirectory, doc_id++); // Save the page

            if (initial_page->depth < maxDepth) {
                // Scan the page and add new links to the bag
                scan_page(initial_page->url, page_content, pages_to_crawl, pages_seen);
            }

            free(page_content); // Free the fetched page content
        }

        webpage_delete(initial_page); // Free the webpage structure
    }

    bag_delete(pages_to_crawl);    // Clean up the bag
    hashtable_delete(pages_seen);  // Clean up the hashtable
}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	// Fill in with your implementation
}

int main(const int argc, char *argv[]) {
	// Fill in with your implementation
}
