#include "Book.h"

BookPointer InitialiseBook(char *title, char *author, int rating, int nrPag)
{
    BookPointer newBook = (BookPointer) malloc(sizeof(Book));

    if(newBook == NULL)
    {
        printf("Initializarea nu a avut loc");
        return NULL;
    }

    newBook->title = (char *) malloc(MAX_BOOK);
    if(newBook->title == NULL)
    {
        printf("Initializarea nu a avut loc");
        free(newBook);
        return NULL;
    }
    strcpy(newBook->title, title);

    newBook->author = (char *) malloc(MAX_AUTHOR);
    if(newBook->author == NULL)
    {
        printf("Initializarea nu a avut loc");
        free(newBook->title);
        free(newBook);
        return NULL;
    }
    strcpy(newBook->author, author);

    newBook->rating = rating;
    newBook->nrPag = nrPag;

    return newBook;
}

void SearchBook(char *key, TrieNodePointer T1,  FILE *outputFile)
{
    BookPointer book = (BookPointer )SearchTrie(T1, key);

    if(book != NULL)
    {
        // then the book exists
        fprintf(outputFile, "Informatii recomandare: %s, %s, %d, %d\n",
                book->title, book->author, book->rating, book->nrPag);
    }
    else
        fprintf(outputFile, "Cartea %s nu exista in recomandarile tale.\n", key);
}

int AddBook(BookPointer toAdd)
{
    return 0;
}

char *AutoCompleteTitle(char *key)
{
    return NULL;
}

char *AutoCompleteAuthor(char *key)
{
    return NULL;
}

void FreeBook(BookPointer *book)
{
    free((*book)->author);
    free((*book)->title);
    free(*book);
}

void FreeAllBooks(BookPointer *books, int nrElem)
{
    int i;
    for(i = 0; i < nrElem; ++i)
    {
        FreeBook(&(books[i]));
    }
}