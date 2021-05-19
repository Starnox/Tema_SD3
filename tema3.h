/* MIHAILESCU Eduard-Florin - 312CB */
#include "utils.h"
#include "TTrie.h"
#include "Book.h"

BookPointer ReadBook(FILE *inputFile);
void DisplayBooksByAuthor(TrieNodePointer trie, FILE *outputile);
void DisplayBooksByAuthorLimit(TrieNodePointer trie, FILE *outputile,
                                int limit, int *current);
void DisplayAuthorsLimit(TrieNodePointer trie, FILE *outputile,
                                int limit, int *current, char *string);

void SearchByAuthor(TrieNodePointer T2, FILE *inputFile, FILE *outputFile);
void SearchBookMain(TrieNodePointer T1, FILE *inputFile, FILE *outputFile);
void AutoCompleteBooks(TrieNodePointer node, char *key, FILE *outputFile);
void AutoCompleteAuthors(TrieNodePointer node, char *key, FILE *outputFile);
void ListAuthor(TrieNodePointer T2, FILE *inputFile, FILE *outputFile);

void DeleteBook(TrieNodePointer *T1, TrieNodePointer *T2, FILE *inputFile, FILE *outputFile);
void RemoveBookFromAuthor(TrieNodePointer *T2, char *title, char *author);