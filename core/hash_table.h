#ifndef HASH_TABLE
#define HASH_TABLE

#define HASH_CAP 20 
#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL
#define LOAD_FACTOR_THRESHOLD 0.7
#define HT_ERROR 1

#include "buffer.h"

typedef struct {
    int v;
    int vt;
    int vn;
} Key;

typedef struct {
    Key key;
    uint32_t value; 
    bool occupied;
    uint64_t hash; // O(n)
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
void ht_print(ht_t* table);
void ht_add(ht_t* table, entry_t* entry, Key key, uint32_t value, size_t capacity);
uint64_t ht_hash(Key key);
bool ht_find(ht_t* table, Key key);
bool ht_key_eq(Key k1, Key k2);
int ht_grow(ht_t* table);
void ht_free(ht_t* table);

void print_obj_vertex(uint32_t index, obj_vertex_t* vertex);
#endif // HASH_TABLE_T
