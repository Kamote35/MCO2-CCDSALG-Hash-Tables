#include <stdio.h> 
#define MAX_HASH 16384
#define MAX_STRINGS 16

// hash.h
// header file for hash functions, collision resolution functoins, helper functions, etc

/*
Notes:

* Hash table size should be set such that it is equal to the first prime number immediately above 1.1 * n

*/

//=======================================================================================================
// typedefs and structs
typedef char string[16]; // not including null byte

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;


//=======================================================================================================
// Prototype functions
int isPrime (int number);
    /*
    Boolean helper function to determine if a number is prime or not

    Parameters:
    number (int) - a non-negative integer to be evaluated if prime or not

    Return:
    1 if number is prime
    0 if number is not prime
    
    */


int nearestPrime (int n);
    /*
    Round up to the next nearest Prime Number

    Parameters:
    int n: a non-negative integer that represents the number of strings in a text.txt file
    
    Return: 
    The prime number that is next to n * 1.1

    */


int hashTableSize (int n);
    /* 
    function that will initialize the hash table size with the restricions indicated in the MCO2 specs pdf

    Parameters:
    int n: a non-negative integer that represents the number of strings in a text.txt file

    Return:
    A size for the Hash Table whose value is the next prime after n * 1.1

    */

Node* createNode(int key, int value);
    /*
    Function that creates a new Node

    Parameters:
    int key: the key of the new Node
    int value: the value of the new Node

    Return:
    A new Node with the key and value specified

    */

HashTable* createHashTable(int size);
    /*
    Function that creates a new Hash Table

    Parameters:
    int size: the size of the new Hash Table

    Return:
    A new Hash Table with the size specified

    */

int hashFunction(int key, int size);
    /*
    Function that hashes the key

    Parameters:
    int key: the key to be hashed
    int size: the size of the Hash Table

    Return:
    The index where the key will be stored in the Hash Table

    */

void insert(HashTable* hashTable, int key, int value);
    /*
    Function that inserts a new Node in the Hash Table

    Parameters:
    HashTable* hashTable: the Hash Table where the Node will be inserted
    int key: the key of the new Node
    int value: the value of the new Node

    */

int search(HashTable* hashTable, int key);
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

