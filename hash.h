#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING_LENGTH 16
#define INITIAL_SIZE 16384

typedef char string[MAX_STRING_LENGTH];

// Define a structure for the key-value pair
typedef struct {
    string key;
    string value;
    int stringComparisons; // Count of string comparisons for each entry
} HashEntry;

// Define a structure for the hash table
typedef struct {
    HashEntry **table;
    int size; // Size of the hash table
    int notHomeAddress; // Count of entries not stored in their home address
    int totalStringComparisons; // Total string comparisons
} HashTable;

// Function prototypes
HashTable* createHashTable();
unsigned int hashFunction(const char* key, int size);
int insertEntry(HashTable* hashTable, const char* key, const char* value);

#endif // HASH_H