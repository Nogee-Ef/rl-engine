#include "header.h"

// form hash value for string key
unsigned hash(char *key, unsigned tableSize) {
    unsigned hashValue;
    for (hashValue = 0; *key != '\0'; key++)
        hashValue = *key + 31 * hashValue;
    return hashValue % tableSize;
}

// initialize and allocate memory for a new hashtable
HashTable *createHashtable(unsigned tableSize) {
    // allocate table
    HashTable *hashTable = calloc(1, sizeof(HashTable)); 

    // allocate table entries
    hashTable->entries = calloc(tableSize, sizeof(Entry*));
    hashTable->tableSize = tableSize;

    return hashTable;
}

Entry *lookup(char *key, HashTable hashTable) {
    Entry *entry;
    Entry **table = hashTable.entries;
    for (entry = table[hash(key, hashTable.tableSize)]; entry != NULL; entry = entry->next)
        if (strcmp(key, entry->key) == 0)
          return entry; /* found */
    return NULL; /* not found */
}

Entry *install(char *key, char *value, HashTable hashTable) {
    Entry *entry;
    Entry **table = hashTable.entries;
    unsigned hashValue;
    
    if ((entry = lookup(key, hashTable)) == NULL) { /* not found */
        entry = (Entry *) malloc(sizeof(*entry));
        if (entry == NULL || (entry->key = strdup(key)) == NULL)
            return NULL;
        hashValue = hash(key, hashTable.tableSize);
        entry->next = table[hashValue];
        table[hashValue] = entry;
    } else /* already there */
        free((void *) entry->value); /*free previous value */
    
    if ((entry->value = strdup(value)) == NULL)
        return NULL;
    
    return entry;
}