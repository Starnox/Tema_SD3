#include "TTrie.h"

TrieNodePointer InitialiseTrieNode()
{
    // alloc memory
    TrieNodePointer newNode = (TrieNodePointer) malloc(sizeof(TrieNode));

    if(newNode == NULL)
    {
        printf("Alocare esuata");
        return NULL;
    }

    newNode->isEnd = 0;
    newNode->endPointer = NULL;

    int i;
    for(i = 0; i < SIGMA; ++i)
        newNode->sons[i] = NULL;

    return newNode;
}

int InsertNode(TrieNodePointer trieNode, char *key, void *endInfo)
{
    TrieNodePointer pointerCrawl = trieNode;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);

        // if the child doesn't exist we create it
        if(!pointerCrawl->sons[currIndex])
            pointerCrawl->sons[currIndex] = InitialiseTrieNode();

        pointerCrawl = pointerCrawl->sons[currIndex];
    }

    pointerCrawl->isEnd = 1;
    pointerCrawl->endPointer = endInfo;
    return 1;
}

// search the trie and if the item exist than return its info
void* SearchTrie(TrieNodePointer node, char *key)
{
    TrieNodePointer pointerCrawl = node;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);

        // if the child doesn't exist we create it
        if(!pointerCrawl->sons[currIndex])
            return NULL;

        pointerCrawl = pointerCrawl->sons[currIndex];
    }
    if(pointerCrawl != NULL && pointerCrawl->isEnd)
        return pointerCrawl->endPointer;
    return NULL;
}


void DeleteTrie(TrieNodePointer *trieNode, int type)
{
    if(*trieNode == NULL)
        return;

    int i;

    if((*trieNode)->isEnd)// if it is end of word
    {
        // if it is of type T1
        if(type == 2)
        {
            // then delete the type 1 trie associated with it
            DeleteTrie((TrieNodePointer *) &((*trieNode)->endPointer), 1);
        }
    }

    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((*trieNode)->sons[i])
        {
            // go deeper in the trie with dfs approach
            DeleteTrie(&((*trieNode)->sons[i]), type);
        }
    }
    // TODO make recursive

    free(*trieNode);
}
