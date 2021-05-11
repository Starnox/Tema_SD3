#include "tema3.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Numar gresit de parametrii introdusi");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    TrieNodePointer T1 = NULL, T2 = NULL;

    
    T1 = InitialiseTrieNode();
    T2 = InitialiseTrieNode();
    if(T1 == NULL || T2 == NULL) // if the init fails
    {
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }  
    
    // this will store all the books information
    // in order to make freeing easier
    BookPointer allBooksInfo[NR_MAX_BOOKS];
    int nrBooks = 0; // this will hold the number of books

    char command[150];
    
    
    while(fscanf(inputFile, "%s", command) != EOF)
    {
        // check for each command
        if(strcmp(command, "add_book") == 0)
        {
            BookPointer newBook = ReadBook(inputFile);// read it
            allBooksInfo[nrBooks++] = newBook; // add to the pool of books

            InsertNode(T1, newBook->title, newBook);// insert the book

            // if the author is not in the T2 trie
            TrieNodePointer authorTrie = SearchTrie(T2, newBook->author);
            if(authorTrie == NULL)
            {
                // we create a new trie that will hold all his books
                TrieNodePointer newTrie = InitialiseTrieNode();

                // we add the current book to his trie
                InsertNode(newTrie, newBook->title, newBook);

                // we insert into T2 the author and his corresponding trie
                InsertNode(T2, newBook->author, newTrie);
            }
            else
            {
                // the author is already in the trie
                // then we just add the book to his trie
                InsertNode(authorTrie, newBook->title, newBook);
            }
        }
        else if(strcmp(command, "search_book") == 0)
        {
            fgetc(inputFile); // get the space

            char *title = NULL;
            size_t length = 0;

            getline(&title, &length, inputFile); // get the book
            if(title[strlen(title) - 1] == '\n')
                title[strlen(title) - 1] = '\0';

            BookPointer book = (BookPointer )SearchTrie(T1, title);

            if(book != NULL)
            {
                // then the book exists
                fprintf(outputFile, "Informatii recomandare: %s, %s, %d, %d\n",
                        book->title, book->author, book->rating, book->nrPag);
            }
            else
                fprintf(outputFile, "Cartea %s nu exista in recomandarile tale.\n", title);

            free(title);
        }
    }
    

    /* teste
    BookPointer book1 = InitialiseBook("ab", "ducu", 10,1);
    InsertNode(T1, "ab", book1);

    InsertNode(T2, "ducu", T1);

    printf("%d\n", SearchTrie(T1, "ab"));

    FreeBook(&book1);

    */
    FreeAllBooks(allBooksInfo, nrBooks);
    DeleteTrie(&T1, 1);
    DeleteTrie(&T2, 2);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

BookPointer ReadBook(FILE *inputFile)
{
    char *line = NULL;
    size_t length = 0;

    char *title, *author, *nrPagString, *ratingString;
    int rating;
    int nrPag;

    fgetc(inputFile); // reads the space

    getline(&line, &length, inputFile); // gets the line after the command

    title = strtok(line, ":");
    if(title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
    
    author = strtok(NULL, ":");
    if(author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';

    ratingString = strtok(NULL, ":");
    if(ratingString[strlen(ratingString) - 1] == '\n')
        ratingString[strlen(ratingString) - 1] = '\0';
    rating = atoi(ratingString);

    nrPagString = strtok(NULL, ":");
    if(nrPagString[strlen(nrPagString) - 1] == '\n')
        nrPagString[strlen(nrPagString) - 1] = '\0';
    nrPag = atoi(nrPagString);

    BookPointer newBook = InitialiseBook(title, author, rating, nrPag);
    free(line);

    return newBook;
}