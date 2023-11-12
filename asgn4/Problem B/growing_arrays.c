#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "growing_arrays.h"

#define NOT_COMMENT_MAIN 1

// print the whole table
void print_table() {
    int i;
    printf("\nTable");
    printf("\n nval: %d", table.nval);
    printf("\n max: %d", table.max);
    printf("\n#######\n");
    for (i = 0; i < table.nval; i++) {
        if (table.record[i].name) {
	    printf("\n %d %d %s", i, table.record[i].id, table.record[i].name);    
	} else {
	    printf("\n %d %d NULL", i, table.record[i].id);    
	}	
    }
    printf("\n#######\n");
}

// returns the index of the item added  
int add_record(Record new_record) {
    Record *new_records;
    int new_size = table.nval + 1;
    printf("\n ADD RECORD: %s", new_record.name);
    print_table();
    if (new_size > table.max) {
	// we need to malloc more 
        printf("\n We need to malloc more: %d", new_size);
        new_records = realloc(table.record, new_size * sizeof(Record));
        if (!new_records) return -1;
        table.record = new_records;
	table.max = new_size;
    }
    table.record[new_size-1] = new_record;
    table.nval = new_size;
    print_table();
    return table.nval - 1;
}

// return 0 if there is no matching record
// return 1 if there is a matching record and deletes it and 
// moves records
int del_record(const char *name) {
    int i, j;
    int found = 0;
    int new_size;

    printf("\n nval: %d", table.nval);
    printf("\n max: %d", table.max);

    for (i = 0; i < table.nval; i++) {
        if (strcmp(table.record[i].name, name) == 0) {
            j = i;
	        found = 1;
	        break;
        }
    }
    if (!found)
        return 0; // No matching record found
		  
    if (j < (table.nval - 1)) {
        for (i = j; i < table.nval; i++) {
            table.record[j].name = table.record[j+1].name;
            table.record[j].id = table.record[j+1].id;
        }
    }
    new_size = table.nval - 1;
    if (new_size > 0) {
        Record *new_records = realloc(table.record, new_size * sizeof(Record));
        if (!new_records) return 0;
        table.record = new_records;
        table.nval--;
		table.max -= 1;
    }
	print_table();
    return (1);
}

// returns id of student record of the first matching record
int get_id(const char *name) {
    for (int i = 0; i < table.nval; i++) {
        if (strcmp(table.record[i].name, name) == 0) {
	    return table.record[i].id;
        }
    }
    return 0;
}

// returns record with a valid index, 0 to max-1 
Record get_record(int index) {
    if (index >= 0 && index < table.nval) {
        return table.record[index];
    }
    // If the index is invalid, return a default Record
    Record empty_record = {0};
    return empty_record;
}

#if NOT_COMMENT_MAIN

// Testing code. You can modify this and check your own test cases.
struct Table table; // If you are using another .c file to test your program comment this line as well.

int main() {
    table.nval = 0;
    table.max = INIT_SIZE;
    table.record = malloc(sizeof(Record) * table.max);

    // test add_record
    Record r1 = {"Alice", 1};
    Record r2 = {"Bob", 2};
    Record r3 = {"Charlie", 3};
    int i1 = add_record(r1);
    int i2 = add_record(r2);
    int i3 = add_record(r3);
    printf("added records at indices %d, %d, %d\n", i1, i2, i3);
    // test get_id and get_record
    int id = get_id("Bob");
    Record r = get_record(i1);
    printf("record at index %d: name=%s, id=%d\n", i1, r.name, r.id);
    printf("record with name 'Bob': id=%d\n", id);
    // test del_record
    int success = del_record("Bob");
    printf("deleted record with name 'Bob': %d\n", success);
    id = get_id("Bob");
    printf("record with name 'Bob': id=%d\n", id);
    free(table.record);
    return 0;
}
#endif

/*
Output for the above testing code:
added records at indices 0, 1, 2
record at index 0: name=Alice, id=1
record with name 'Bob': id=2
deleted record with name 'Bob': 1
record with name 'Bob': id=0
*/
