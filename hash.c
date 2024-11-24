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

// Insert a key-value pair into the hash table
void insert(HashTable* hashTable, const char* key, int value) {
    unsigned int index = hashFunction(key, hashTable->size);

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// Search for a key in the hash table
int search(HashTable* hashTable, const char* key) {
    unsigned int index = hashFunction(key, hashTable->size);
    Node* current = hashTable->table[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

// Free the memory used by the hash table
void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Node* current = hashTable->table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}
