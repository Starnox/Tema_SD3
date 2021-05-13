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
    if(trieNode == NULL)
        return 0;
    TrieNodePointer pointerCrawl = trieNode;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);
        if(pointerCrawl == NULL)
            return 0;

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
    if(node == NULL)
        return NULL;
    TrieNodePointer pointerCrawl = node;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);

        if(!pointerCrawl->sons[currIndex])
            return NULL;

        pointerCrawl = pointerCrawl->sons[currIndex];
    }
    if(pointerCrawl != NULL && pointerCrawl->isEnd)
        return pointerCrawl->endPointer;
    return NULL;
}

// check if the node has any sons
int IsEmpty(TrieNodePointer node)
{
    int i;
    for(i = 0; i < SIGMA; ++i)
    {
        if(node->sons[i] != NULL)
            return 0;
    }
    return 1;
}


TrieNodePointer Remove(TrieNodePointer *node, char *key, int depth, FreeFunction freeFunc)
{
    if(*node == NULL)
        return NULL;

    // if it is the last character of the key
    if(depth == strlen(key))
    {
        // if is no prefix to any other word
        if(IsEmpty(*node))
        {
            DeleteTrie(node, 1, freeFunc);
            *node = NULL;
        }
        if(*node != NULL && (*node)->isEnd)
        {
            if(freeFunc != NULL)
            {
                freeFunc(&((*node)->endPointer));
            }
            (*node)->isEnd = 0;
        }
        return *node;
    }
    int index = GetIndexInAlphabet(key[depth]);

    (*node)->sons[index] = Remove(&(*node)->sons[index], key, depth + 1, freeFunc);

    // if the node does not have any child and is not end of another word
    if(IsEmpty(*node) && (*node)->isEnd == 0)
    {
        DeleteTrie(node, 1, freeFunc);
        *node = NULL;
    }
    return *node;
}


void DeleteTrie(TrieNodePointer *trieNode, int type, FreeFunction freeFunc)
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
            DeleteTrie((TrieNodePointer *) &((*trieNode)->endPointer), 1, freeFunc);
        }
        else
        {
            if(freeFunc != NULL)
                freeFunc(&((*trieNode)->endPointer));
        }

    }

    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((*trieNode)->sons[i])
        {
            // go deeper in the trie with dfs approach
            DeleteTrie(&((*trieNode)->sons[i]), type, freeFunc);
        }
    }

    free(*trieNode);
    *trieNode = NULL;
}
