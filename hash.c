#include "hash.h"
#include <math.h>

// Check if a number is prime
int isPrime(int number) {
    if (number <= 1) return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

// Find the nearest prime greater than n * 1.1
int nearestPrime(int n) {
    int candidate = (int)ceil(n * 1.1);
    while (!isPrime(candidate)) {
        candidate++;
    }
    return candidate;
}

// Create a hash table
HashTable* createHashTable(int n) {
    int primeSize = nearestPrime(n);
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash table\n");
        return NULL;
    }
    hashTable->table = (HashEntry**)malloc(primeSize * sizeof(HashEntry*));
    if (hashTable->table == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash table entries\n");
        free(hashTable);
        return NULL;
    }
    for (int i = 0; i < primeSize; i++) {
        hashTable->table[i] = NULL;
    }
    hashTable->size = primeSize;
    hashTable->notHomeAddress = 0;
    hashTable->totalStringComparisons = 0;
    return hashTable;
}

// Hash function using modulo operation
unsigned int hashFunction(const char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key++) % size;
    }
    return hash;
}

// Insert an entry into the hash table
int insertEntry(HashTable* hashTable, const char* key, const char* value) {
    unsigned int index = hashFunction(key, hashTable->size);
    unsigned int originalIndex = index;
    int comparisons = 0;

    while (hashTable->table[index] != NULL) {
        comparisons++;
        if (strcmp(hashTable->table[index]->key, key) == 0) {
            // Update the value if the key already exists
            strcpy(hashTable->table[index]->value, value);
            hashTable->table[index]->stringComparisons += comparisons;
            hashTable->totalStringComparisons += comparisons;
            return 0;
        }
        index = (index + 1) % hashTable->size;
        if (index == originalIndex) {
            // The table is full
            return -1;
        }
    }

    // Insert the new entry
    HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
    if (newEntry == NULL) {
        fprintf(stderr, "Failed to allocate memory for hash entry\n");
        return -1;
    }
    strcpy(newEntry->key, key);
    strcpy(newEntry->value, value);
    newEntry->stringComparisons = comparisons;
    hashTable->table[index] = newEntry;

    if (index != originalIndex) {
        hashTable->notHomeAddress++;
    }
    hashTable->totalStringComparisons += comparisons;

    return 0;
}
