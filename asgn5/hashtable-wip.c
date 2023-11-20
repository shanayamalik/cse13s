#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "set.h"

typedef struct hashtable {
    int num_slots;
    set_t **table;
} hashtable_t;

static int hash_function(const char *key, int num_slots) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % num_slots;
}

hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->num_slots = num_slots;
    ht->table = malloc(sizeof(set_t *) * num_slots);
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < num_slots; i++) {
        ht->table[i] = set_new();
        if (ht->table[i] == NULL) {
            // Cleanup in case of allocation failure
            for (int j = 0; j < i; j++) {
                set_delete(ht->table[j], NULL);
            }
            free(ht->table);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL) {
        return false;
    }

    int index = hash_function(key, ht->num_slots);
    if (set_find(ht->table[index], key) != NULL) {
        // Key already exists
        return false;
    }

    return set_insert(ht->table[index], key, item);
}

void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    int index = hash_function(key, ht->num_slots);
    return set_find(ht->table[index], key);
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return;
    }
    if (ht == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }
    if (itemprint == NULL) {
        fprintf(fp, "()\n");
        return;
    }
    for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->table[i], fp, itemprint);
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }
    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->table[i], arg, itemfunc);
    }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }
    for (int i = 0; i < ht->num_slots; i++) {
        set_delete(ht->table[i], itemdelete);
    }
    free(ht->table);
    free(ht);
}

void hashtable_remove(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return;
    }

    int index = hash_function(key, ht->num_slots);
    // Assuming set_remove is a function that removes a key-item pair from the set
    set_remove(ht->table[index], key);
}

