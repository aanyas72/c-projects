#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 50

typedef struct item {
    char* key;
    char* value;
} item;

typedef struct HashMap {
    item **items; // pointer to an array of pointers to item structs
    int size;
    int count;
} HashMap;

// Create a new hash table item
item* create_item(const char* key, const char* value) {
    item* i = (item*) malloc(sizeof(i));
    i->key = strdup(key); // Duplicate string for key
    i->value = strdup(value); // Duplicate string for value
    return i;
}

unsigned long hash_function(const char* str) {
    unsigned long i = 0;
    for (int j = 0; str[j]; j++) {
        i += str[j];
    }
    return i % TABLE_SIZE; // TABLE_SIZE is the size of your hash table array
}