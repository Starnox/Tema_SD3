/* MIHAILESCU Eduard-Florin - 312CB */
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
void FreeBook(void **info);


#endif