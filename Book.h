#include "utils.h"
#include "TTrie.h"

#ifndef BOOK_H
#define BOOK_H

typedef struct book
{
    char *title;
    char *author;
    int rating;
    int nrPag;
}Book, *BookPointer;


BookPointer InitialiseBook(char *title, char *author, int rating, int nrPag);
void SearchBook(char *key, TrieNodePointer T1, FILE *outputFile);
int AddBook(BookPointer toAdd);
char *AutoCompleteTitle(char *key);
char *AutoCompleteAuthor(char *key);

void FreeBook(BookPointer *book);
void FreeAllBooks(BookPointer *books, int nrElem);

#endif