#include "pagedir.h"           // Include header for page directory functions
#include "crawler.h"           // Include header for crawler-specific structures
#include <stdio.h>             // Include for standard I/O functions
#include <stdlib.h>            // Include for standard library functions
#include <string.h>            // Include for string handling functions
#include <sys/stat.h>          // Include for file status functions

// Initialize the page directory
bool pagedir_init(const char *pageDirectory) {
    struct stat directoryStat;        // Declare a stat structure to store directory info
    // Check if the directory exists and is a directory
    if (stat(pageDirectory, &directoryStat) != 0 || !S_ISDIR(directoryStat.st_mode)) {
        fprintf(stderr, "Page directory does not exist or is not a directory\n");
        exit(5);                // Exit if the directory check fails
    }

    char filePath[256];         // Buffer to hold the complete file path
    // Create the path for the file to mark the directory
    snprintf(filePath, sizeof(filePath), "%s/any_name.crawler", pageDirectory);
    FILE *fp = fopen(filePath, "w"); // Open the file for writing
    if (fp == NULL) {           // Check if file opening failed
        fprintf(stderr, "Unable to create file in page directory\n");
        exit(6);                // Exit if file creation fails
    }
    fclose(fp);                 // Close the file
    return true;                // Return true if initialization is successful
}

// Save a webpage to the page directory
void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID) {
    // Validate the input parameters
    if (page == NULL || pageDirectory == NULL) {
        fprintf(stderr, "Invalid parameters in pagedir_save\n");
        return;                 // Return if inputs are invalid
    }

    char filePath[256];         // Buffer to hold the complete file path
    // Create the path for the file using the document ID
    snprintf(filePath, sizeof(filePath), "%s/%d", pageDirectory, docID);
    FILE *fp = fopen(filePath, "w"); // Open the file for writing
    if (fp == NULL) {           // Check if file opening failed
        fprintf(stderr, "Unable to open file for writing in page directory\n");
        return;                 // Return if file opening fails
    }

    // Write the URL, depth, and HTML content to the file
    fprintf(fp, "%s\n%d\n%s", page->url, page->depth, page->html);
    fclose(fp);                 // Close the file
}
