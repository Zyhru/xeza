#include "hash_table.h"
#include <stdint.h>

void ht_print_key_value(Key key, unsigned int value) {
    printf("Key -> {%u/%u/%u}\n", key.v, key.vt, key.vn);
    printf("Value -> {%u}\n", value);
}

ht_t* ht_create() {
    ht_t* hash_table = malloc(sizeof(ht_t));
    if(hash_table == NULL) {
        fprintf(stderr, "Unable to allocate memory for ht.");
        return NULL;
    }

    hash_table->capacity = HASH_CAP;
    hash_table->size = 0;
    hash_table->entries = calloc(hash_table->capacity, sizeof(entry_t));
    if(hash_table->entries == NULL) {
        fprintf(stderr, "Unable to allocate memory for table entry.");
        return NULL;
    }

    return hash_table;
}

void ht_insert(ht_t* table, entry_t entry) {
    double load_factor = (double) table->size / table->capacity; 
    printf("Load factor %lf\n", load_factor);
    if(load_factor >= LOAD_FACTOR_THRESHOLD) {
        if(ht_grow(table) == HT_ERROR) {
            fprintf(stderr, "Failed to regrow table\n");
            exit(EXIT_FAILURE);
        }
    }
    
    //printf("Hash Table Size %zu\n", table->size);
    ht_add(table, table->entries, entry.key, entry.value, table->capacity);
}

bool ht_key_eq(Key k, Key q) {
    return (k.v == q.v && k.vt == q.vt && k.vn == q.vn);
}

// on regrow it will have issues because the hash % table->cap will
// result in a different index since the table->cap will be different
// meaning I should should linear probe, if only if when the hash has been the same
void ht_add(ht_t* table, entry_t* entries, Key key, unsigned int value, size_t capacity) {
    uint64_t hash = ht_hash(key); // will get the same hash as earlier
    uint64_t index = hash % capacity;
    entries[index].hash = hash;

    //printf("Hash = %lu : (%u/%u/%u)\n", hash, key.v, key.vt, key.vn);

    // is index occupied
    while(entries[index].occupied) {
        if(ht_key_eq(entries[index].key, key)) {
            printf("Key already in table. Updating value!\n");
            entries[index].value = value;
            return;
        }
        
        index = (index + 1) % capacity; // wrapping around
    }

    //printf("Index being used for hash {%lu = %lu}\n", hash, index);
    printf("new key : value.. inserting for the first time\n");
    entries[index].key = key;
    entries[index].value = value;
    entries[index].occupied = true;
    table->size++;
}

/*
    * We have to linear probe because when searching for a key
    * there could be multiple key with the same hash code just at 
    * different indexes.
    *
*/

// when finding it should find based on the index, it should find on the hash
// there could many keys with the same hash, but what solves this issue if we have the same hash
// but also check if the key being inserted is the same 
entry_t* ht_find(ht_t *table, Key key) {
    if (table->capacity == 0) return NULL;
    uint64_t hash = ht_hash(key);
    uint64_t index = hash % table->capacity;

    //printf("Index being searched for %lu\n", index);
    while(table->entries[index].occupied) { // fail, when it regrows it has a new capacity, which can generate an index that is not occupied
        if(ht_key_eq(table->entries[index].key, key)) {
            printf("Key has been found = {%u/%u/%u}\n", key.v, key.vt, key.vn);
            return &table->entries[index];
        }

        index = (index + 1) % table->capacity;
    }
   
    printf("Could not find key\n");
    return NULL; 
}

uint64_t ht_hash(Key key) {
    uint64_t hash = FNV_OFFSET_BASIS;
    uint8_t* ptr = (uint8_t *) &key;
    
    for(size_t i = 0; i < sizeof(key); i++) {
        hash ^= (uint64_t)ptr[i];
        hash *= FNV_PRIME;
        //printf("byte %zu = %u\n", i, ptr[i]);
    }
    
    return hash;
}

void ht_print_table(ht_t* table) {
    //INFO: // Can just iterate over occupied?
    for(int i = 0; i < table->capacity; ++i) { 
        if(table->entries[i].occupied) {
            Key key = table->entries[i].key;
            unsigned int value = table->entries[i].value;
            ht_print_key_value(key, value);
        }
    }

    printf("Hash Table size: %zu\n", table->size); 
}

int ht_grow(ht_t* table) {
    //printf("Regrowing!\n");
    size_t new_cap = 2 * table->capacity;
    if(new_cap < table->capacity) {
        fprintf(stderr, "New capacity is less than table->capacity");
        return 1;
    }

    entry_t* new_entry = calloc(new_cap, sizeof(entry_t));
    if(new_entry == NULL) return 1;
    
    table->size = 0;
    for(size_t i = 0; i < table->capacity; ++i) {
        if(table->entries[i].occupied) {
            entry_t entry = table->entries[i];
            ht_add(table, new_entry, entry.key, entry.value, new_cap);
        }
    }
  
    //ht_print(table);
    free(table->entries);
    table->entries = new_entry; 
    table->capacity = new_cap;
    return 0;
}


void ht_free(ht_t* table) {
    free(table);
    free(table->entries);
}

