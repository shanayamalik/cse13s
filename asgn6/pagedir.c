#include "pagedir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crawler.h"

/* Initializes the page directory for saving web pages, by creating a crawler file. If the directory that saves web pages is initialized, it will return true. */
bool pagedir_init(const char *pageDirectory) {
    char filename[256];
    // Construct the path for the '.crawler' file
    snprintf(filename, sizeof(filename), "%s/.crawler", pageDirectory);
    // Try to create the file
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        // Error handling if file creation fails
        fprintf(stderr, "Error: Unable to create .crawler file in %s\n", pageDirectory);
        return false;
    }
    // Close the file and return true
    fclose(fp);
    return true;
}

/* Saves a webpage to the specified page directory with a unique document ID. The file is named using the document ID, and contains the URL, depth, and HTML content of the page. */
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s/%d", pageDirectory, docID);
    // Try to write in the file
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        // Error handling if file opening fails
        fprintf(stderr, "Error: Unable to write to file %s\n", filename);
        return;
    }
    // Write the URL, depth, and HTML content to the file
    fprintf(fp, "%s\n%d\n%s", page->url, page->depth, page->html);
    fclose(fp);
}
