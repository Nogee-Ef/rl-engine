#include "header.h"

// form hash value for string key
unsigned hash(char *key, unsigned tableSize) {
    unsigned hashval;
    for (hashval = 0; *key != '\0'; key++)
      hashval = *key + 31 * hashval;
    return hashval % tableSize;
}

// initialize and allocate memory for a new hashtable
hashtable_t *createHashtable(unsigned tableSize) {
    // allocate table
    hashtable_t *hashtable = calloc(1, sizeof(hashtable_t)); 

    // allocate table entries
    hashtable->entries = calloc(tableSize, sizeof(entry_t*));
    hashtable->tableSize = tableSize;

    return hashtable;
}

entry_t *lookup(char *key, hashtable_t hashtable) { //entry_t *hashtable[TABLESIZE]) {
    entry_t *entry;
    entry_t **table = hashtable.entries;
    for (entry = table[hash(key, hashtable.tableSize)]; entry != NULL; entry = entry->next)
        if (strcmp(key, entry->key) == 0)
          return entry; /* found */
    return NULL; /* not found */
}

entry_t *install(char *key, char *value, hashtable_t hashtable) {
    entry_t *entry;
    entry_t **table = hashtable.entries;
    unsigned hashval;
    if ((entry = lookup(key, hashtable)) == NULL) { /* not found */
        entry = (entry_t *) malloc(sizeof(*entry));
        if (entry == NULL || (entry->key = strdup(key)) == NULL)
          return NULL;
        hashval = hash(key, hashtable.tableSize);
        entry->next = table[hashval];
        table[hashval] = entry;
    } else /* already there */
        free((void *) entry->value); /*free previous value */
    if ((entry->value = strdup(value)) == NULL)
       return NULL;
    return entry;
}