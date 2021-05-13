#include "utils.h"

#ifndef TTrie_H
#define TTrie_H

typedef struct trie
{
    struct trie *sons[SIGMA];

    int isEnd;
    void *endPointer;
}TrieNode, *TrieNodePointer;

typedef void (*FreeFunction)(void **);

TrieNodePointer InitialiseTrieNode();
void DeleteTrie(TrieNodePointer *trieNode, int type, FreeFunction freeFunc);
int InsertNode(TrieNodePointer trieNode, char *key, void *endInfo); // (0/1) success
void* SearchTrie(TrieNodePointer node, char *key);


int IsEmpty(TrieNodePointer node);
TrieNodePointer Remove(TrieNodePointer *node, char *key, int depth, FreeFunction freeFunc);

#endif