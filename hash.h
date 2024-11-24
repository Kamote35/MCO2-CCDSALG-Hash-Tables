#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRING_LENGTH 16
#define MAX_HASH 16384
#define MAX_STRINGS 16

typedef char string[MAX_STRING_LENGTH]; // Defines a string with 16 characters

// Node structure for chaining
typedef struct {
    char* key;
    int value;
    int isOccupied; // Flag to indicate if the slot is occupied
} HashTableEntry;

// Hash table structure
typedef struct {
    int size;
    HashTableEntry* table;
} HashTable;

// Function prototypes
int isPrime(int number);
    /*
    Boolean helper function to determine if a number is prime or not

    Parameters:
    number (int) - a non-negative integer to be evaluated if prime or not

    Return:
    1 if number is prime
    0 if number is not prime
    
    */
int nearestPrime(int n);
    /*
    Round up to the next nearest Prime Number

    Parameters:
    int n: a non-negative integer that represents the number of strings in a text.txt file
    
    Return: 
    The prime number that is next to n * 1.1

    */
HashTable* createHashTable(int size);
    /*
    Function that creates a new Node

    Parameters:
    int key: the key of the new Node
    int value: the value of the new Node

    Return:
    A new Node with the key and value specified

    */
unsigned int hashFunction(const char* key, int size);

void insert(HashTable* hashTable, const char* key, int value);
    /*
    Function that inserts a new Node in the Hash Table

    Parameters:
    HashTable* hashTable: the Hash Table where the Node will be inserted
    int key: the key of the new Node
    int value: the value of the new Node

    */
int search(HashTable* hashTable, const char* key);
    /*
    Function that searches for a key in the Hash Table

    Parameters:
    HashTable* hashTable: the Hash Table where the key will be searched
    int key: the key to be searched

    Return:
    The value of the key if found
    -1 if the key is not found

    */
void freeHashTable(HashTable* hashTable);
    /*
    Function that frees the memory allocated for the Hash Table

    Parameters:
    HashTable* hashTable: the Hash Table to be freed

    */

#endif
