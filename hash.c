#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

unsigned int hash(const char* str) {                                //fonction de hachage (désigne l'index)
    unsigned int h = 0;                                             //unsigned int : entier qui peut être négatif
    while (*str) {                                                  //tant que l'on ne point pas sur \0
        h = h * 31 + (unsigned char)*str;                           //hachage (31 car nombre premier encore), str++ pour passer au caractère suivant
        str++;
    }
    return h % HASH_SIZE;
}

void hash_init(HashTable* ht) {                                     //initialise toutes les nodes à NULL
    for (int i=0;i<HASH_SIZE;i++) {                                 
        ht->table[i] = NULL;
    }
}

void hash_insert(HashTable* ht, const char* key, int index){        //crée une node et l'insère en utilisant la fonction hash()
    unsigned int h = hash(key);
    HashNode* node = malloc(sizeof(HashNode));
    if (!node) {return;}                                            //si pas assez de mémoire on arrête
    strcpy(node->key,key);
    node->index = index;
    node->next = ht->table[h];                                      //on relie
    ht->table[h] = node;                                            //et on affecte
}

int hash_find(HashTable* ht, const char* key) {                     //trouve la node que l'on veut
    unsigned int h = hash(key);
    HashNode* cur = ht->table[h];
    while (cur) {                                                   //tant qu'on a des nodes
        if (strcmp(cur->key, key) == 0)                             
            return cur->index;
        cur = cur->next;
    }
    return -1;
}

void hash_free(HashTable* ht) {                                     //libère la mémoire utilisée par toute la hash table
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* cur = ht->table[i];
        while (cur) {
            HashNode* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

