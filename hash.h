#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 211                       //un nombre premier plus grand que le nombre de stations qui permettra d'assigner la place aux stations
#define NAME 50

typedef struct HashNode {
    char key[NAME];
    int index;
    struct HashNode* next;
}HashNode;

typedef struct HashTable{
    HashNode* table[HASH_SIZE];
}HashTable;

unsigned int hash(const char* key);
void hash_init(HashTable* ht);
void hash_insert(HashTable* ht, const char* key, int index);
int hash_find(HashTable* ht, const char* key);
void hash_free(HashTable* ht);

#endif

