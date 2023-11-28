#include "pagedir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crawler.h"

bool pagedir_init(const char *pageDirectory) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s/.crawler", pageDirectory);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to create .crawler file in %s\n", pageDirectory);
        return false;
    }

    fclose(fp);
    return true;
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int docID) {
    char filename[256];
    snprintf(filename, sizeof(filename), "%s/%d", pageDirectory, docID);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to write to file %s\n", filename);
        return;
    }

    fprintf(fp, "%s\n%d\n%s", page->url, page->depth, page->html);
    fclose(fp);
}
