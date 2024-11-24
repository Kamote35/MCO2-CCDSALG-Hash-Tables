#include "hash.h"

int main() {
    char inFile_name[100];
    char outFile_name[100];
    string* words;
    int nWords;
    int i;

    // Input file name
    printf("Please enter the name of the input file: ");
    scanf("%s", inFile_name);

    FILE* pInputFile = fopen(inFile_name, "r");
    if (!pInputFile) {
        printf("Cannot open input file.\n");
        return 1;
    }

    // Read the number of words
    fscanf(pInputFile, "%d", &nWords);

    // Allocate memory for the words
    words = malloc(nWords * sizeof(string));
    if (!words) {
        printf("Memory allocation failed.\n");
        fclose(pInputFile);
        return 1;
    }

    // Read words from the file
    for (i = 0; i < nWords; i++) {
        fscanf(pInputFile, "%s", words[i]);
    }
    fclose(pInputFile);

    // Output file name
    printf("Please enter the name of the output file: ");
    scanf("%s", outFile_name);

    FILE* pOutputFile = fopen(outFile_name, "w");
    if (!pOutputFile) {
        printf("Cannot open output file.\n");
        free(words);
        return 1;
    }

    // Create hash table
    int tableSize = nearestPrime(nWords);
    HashTable* hashTable = createHashTable(tableSize);

    int notStoredInHomeAddress = 0; // int storedInHomeAddress = 0;
    int totalComparisons = 0, totalStringsStored = 0;

    // Insert words into the hash table
    for (i = 0; i < nWords; i++) {
        if (search(hashTable, words[i]) == -1) { // Avoid duplicates
            insert(hashTable, words[i], 1, &notStoredInHomeAddress, &totalComparisons);
            totalStringsStored++;
        }
    }

    // Write statistics
    fprintf(pOutputFile, "%d\n%d\n%d\n%d\n%.6f\n",
            nWords, totalStringsStored, totalStringsStored - notStoredInHomeAddress, notStoredInHomeAddress,
            (double)totalComparisons / totalStringsStored);

    // Write hash table content
    for (i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i]) {
            unsigned int homeIndex = hashFunction(hashTable->table[i]->key, hashTable->size);
            fprintf(pOutputFile, "%d %s %d %s %d\n",
                    i, hashTable->table[i]->key, homeIndex,
                    (i == homeIndex) ? "YES" : "NO", 1);
        } else {
            fprintf(pOutputFile, "%d --- --- --- ---\n", i);
        }
    }

    // Cleanup
    fclose(pOutputFile);
    freeHashTable(hashTable);
    free(words);

    printf("Output written to %s\n", outFile_name);
    return 0;
}