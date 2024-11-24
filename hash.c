#include <stdio.h>
#include <math.h>
#include "hash.h"

// hash.c
// C source file for hash function, etc
// define prototype functions here

int isPrime (int number) { // helper function that returns a boolean value
    if (number <= 1) { // return 0 if number is less than or equal to 1
        return 0;
    }
    for (int i = 2; i < number; i++) { // check if number is divisible by any number from 2 to (number - 1)
        if (number % i == 0) {
            return 0; // return 0 if divisible by any number
        }
    }
    return 1; // return 1 if prime
}

int nearestPrime (int n) { // helper function that returns the nearest prime 
    int number = floor(n * 1.1);

    int isFound = 0; // sentinel value used to control the while loop
    while (!isFound) { // loop until a prime number is found
        number++; // at first iteration, immediately increments by 1 as stated on the MCO2 specs pdf
        if (isPrime(number)) {
            isFound = 1; // break out of the while-loop  
            return number;
        }
    }
}

int hashTableSize (int n) { // function that returns the Table Size with the requirements specified in the MCO2 specs pdf

    return nearestPrime (n);
}

Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->table = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

int hashFunction(int key, int size) {
    return key % size;
}

void insert(HashTable* hashTable, int key, int value) {
    int index = hashFunction(key, hashTable->size);
    Node* newNode = createNode(key, value);
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = newNode;
    } else {
        Node* temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int search(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    Node* temp = hashTable->table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1; // Key not found
}

void freeHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Node* temp = hashTable->table[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

