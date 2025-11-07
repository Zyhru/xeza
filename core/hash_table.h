#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define HASH_CAP 20 
#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL
#define LOAD_FACTOR_THRESHOLD 0.7
#define HT_ERROR 1

#include "api.h"

typedef struct {
    int v;
    int vt;
    int vn;
} vertex_key_t;

typedef struct {
    vertex_key_t key;
    unsigned int value; 
    bool occupied;
} entry_t;

typedef struct {
    size_t size;
    size_t capacity;
    entry_t* entries;
} ht_t;

// create
// find
// add
// hash function
// regrow -> i hope i dont need this

ht_t* ht_create();
void ht_insert(ht_t* table, entry_t entry);
void ht_print_table(ht_t* table);
void ht_print_key_value(vertex_key_t key, unsigned int value);
void ht_add(ht_t* table, entry_t* entry, vertex_key_t key, unsigned int value, size_t capacity);
uint64_t ht_hash(vertex_key_t key);
entry_t* ht_find(ht_t* table, vertex_key_t key);
bool ht_key_eq(vertex_key_t k1, vertex_key_t k2);
int ht_grow(ht_t* table);
void ht_free(ht_t* table);

#endif // HASH_TABLE_H
