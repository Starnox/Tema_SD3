#include "utils.h"

#ifndef TTrie_H
#define TTrie_H

typedef struct trie
{
    struct trie *sons[SIGMA];

    int isEnd;
    void *endPointer;
}TrieNode, *TrieNodePointer;

TrieNodePointer InitialiseTrieNode();
void DeleteTrie(TrieNodePointer *trieNode, int type);
int InsertNode(TrieNodePointer trieNode, char *key, void *endInfo); // (0/1) success
void* SearchTrie(TrieNodePointer node, char *key);

#endif