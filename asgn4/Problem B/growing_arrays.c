#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "growing_arrays.h"

#define NOT_COMMENT_MAIN 1

struct Table shanaya_table;

// returns the index of the item added  
int add_record(Record new_record) {
    Record *new_records;
    // printf("\n Adding %s", new_record.name);
    int new_size = shanaya_table.nval + 1;
    if (shanaya_table.record == 0)
        new_records = malloc(new_size * sizeof(Record));
    else
        new_records = realloc(shanaya_table.record, new_size * sizeof(Record));
    if (!new_records) return -1;
    shanaya_table.record = new_records;
    shanaya_table.record[shanaya_table.nval] = new_record;
    shanaya_table.nval++;
    return shanaya_table.nval - 1;
}

// print the whole table
void print_table() {
    int i;
    printf("\n Print Table");
    for (i = 0; i < shanaya_table.nval; i++) {
	printf("\n %d %s", shanaya_table.record[i].id, shanaya_table.record[i].name);    
    }
    printf("DONE \n");
}

// return 0 if there is no matching record
// return 1 if there is a matching record and deletes it and 
// moves records
int del_record(const char *name) {
    int i, j;
    int found = 0;
    int new_size;

    for (i = 0; i < shanaya_table.nval; i++) {
        if (strcmp(shanaya_table.record[i].name, name) == 0) {
            j = i;
	    found = 1;
	    break;
        }
    }
    if (!found)
        return 0; // No matching record found
		  
    if ( j < (shanaya_table.nval - 1)) {
        for (i = j; i < shanaya_table.nval; i++) {
            shanaya_table.record[j].name = shanaya_table.record[j+1].name;
            shanaya_table.record[j].id = shanaya_table.record[j+1].id;
        }
    }
    new_size = shanaya_table.nval - 1;
    if (new_size == 0) {
        free(shanaya_table.record);
        shanaya_table.record = 0;
        shanaya_table.nval = 0;
    } else {
        Record *new_records = realloc(shanaya_table.record, new_size * sizeof(Record));
        if (!new_records) return 0;
        shanaya_table.record = new_records;
        shanaya_table.nval--;
    }
    return (1);
} 

// returns id of student record of the first matching record
int get_id(const char *name) {
    for (int i = 0; i < shanaya_table.nval; i++) {
        if (strcmp(shanaya_table.record[i].name, name) == 0) {
	    return shanaya_table.record[i].id;
        }
    }
    return 0;
}

// returns record with a valid index, 0 to max-1 
Record get_record(int index) {
    if (index >= 0 && index < shanaya_table.nval) {
        return shanaya_table.record[index];
    }
    // If the index is invalid, return a default Record
Record empty_record = {0};
    return empty_record;
}

#if NOT_COMMENT_MAIN

// Testing code. You can modify this and check your own test cases.
int main() {
    shanaya_table.nval = 0;
    shanaya_table.record = 0;

    // test add_record
    Record r1 = {"Alice", 1};
    Record r2 = {"Bob", 2};
    Record r3 = {"Charlie", 3};

    printf("nval =%d\n", shanaya_table.nval);
    int i1 = add_record(r1);
    print_table();

    printf("nval =%d\n", shanaya_table.nval);
    int i2 = add_record(r2);
    print_table();

    printf("nval =%d\n", shanaya_table.nval);
    int i3 = add_record(r3);
    print_table();
    printf("nval =%d\n", shanaya_table.nval);
    printf("added records at indices %d, %d, %d\n", i1, i2, i3);

    // test del_record
    printf("deleting  record with name 'Charlie'\n");
    del_record("Charlie");
    print_table();
    printf("nval =%d\n", shanaya_table.nval);

    // test del_record
    printf("deleting  record with name 'Bob\n");
    del_record("Bob");
    print_table();
    printf("nval =%d\n", shanaya_table.nval);

    // test del_record
    printf("deleting record with name 'Alice'\n");
    del_record("Alice");
    print_table();
    printf("nval =%d\n", shanaya_table.nval);

    printf("nval =%d\n", shanaya_table.nval);
    if (shanaya_table.nval > 0)
        free(shanaya_table.record);
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
