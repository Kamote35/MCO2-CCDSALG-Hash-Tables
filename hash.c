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

// Create a new hash table
HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->table = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
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

// Quadratic probing for insertion
/*void insert(HashTable* hashTable, const char* key, int value) {
    // Check if the key already exists in the hash table
    if (search(hashTable, key) != -1) {
        printf("Key '%s' already exists in the hash table.\n", key);
        return;
    }

    unsigned int index = hashFunction(key, hashTable->size);
    unsigned int originalIndex = index;
    int i = 1;

    while (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->key, key) != 0) {
        index = (originalIndex + i * i) % hashTable->size;
        i++;
        if (i >= hashTable->size) {
            printf("Hash table is full, cannot insert %s\n", key);
            return;
        }
    }

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = (Node*)malloc(sizeof(Node));
        hashTable->table[index]->key = strdup(key);
        hashTable->table[index]->value = value;
        hashTable->table[index]->isOccupied = 1;
    } else {
        // Update value if the key already exists
        hashTable->table[index]->value = value;
    }
}
*/

void insert(HashTable* hashTable, const char* key, int value, int* notStoredInHomeAddress, int* totalComparisons) {
    unsigned int index = hashFunction(key, hashTable->size);
    unsigned int originalIndex = index;
    int i = 1, comparisons = 1;

    while (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->key, key) != 0) {
        index = (originalIndex + i * i) % hashTable->size;
        i++;
        comparisons++;
        if (i >= hashTable->size) {
            printf("Hash table is full, cannot insert %s\n", key);
            return;
        }
    }

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = (Node*)malloc(sizeof(Node));
        hashTable->table[index]->key = strdup(key);
        hashTable->table[index]->value = value;
        hashTable->table[index]->next = NULL;

        if (index != originalIndex) {
            (*notStoredInHomeAddress)++; // Increment for relocation
        }
    } else {
        hashTable->table[index]->value = value; // Update value if key exists
    }

    *totalComparisons += comparisons; // Update total comparisons
}


// Quadratic probing for searching
int search(HashTable* hashTable, const char* key) {
    unsigned int index = hashFunction(key, hashTable->size);
    unsigned int originalIndex = index;
    int i = 1;

    while (hashTable->table[index] != NULL) {
        if (strcmp(hashTable->table[index]->key, key) == 0) {
            return hashTable->table[index]->value;
        }
        index = (originalIndex + i * i) % hashTable->size;
        i++;
        if (i >= hashTable->size) {
            return -1; // Not found
        }
    }
    return -1; // Not found
}

// Free the memory used by the hash table
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            free(hashTable->table[i]->key);
            free(hashTable->table[i]);
        }
    }
    free(hashTable->table);
    free(hashTable);
}
