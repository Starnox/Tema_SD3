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
    //BookPointer allBooksInfo[NR_MAX_BOOKS];
    //int nrBooks = 0; // this will hold the number of books

    char command[150];
    
    
    while(fscanf(inputFile, "%s", command) != EOF)
    {
        if(T1 == NULL)
        {
            T1 = InitialiseTrieNode();
            if(T1 == NULL)
                return 1;
        }
        if(T2 == NULL)
        {
            T2 = InitialiseTrieNode();
            if(T2 == NULL)
                return 1;
        }
        // check for each command
        if(strcmp(command, "add_book") == 0)
        {
            BookPointer newBook = ReadBook(inputFile);// read it
            if(SearchTrie(T1, newBook->title) != NULL)
            {
                // the book already exists
                FreeBook((void **) &newBook);
                continue;
            }
            

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
                // the author is already in the T2 trie
                // then we just add the book to his trie
                InsertNode(authorTrie, newBook->title, newBook);
            }
        }
        else if(strcmp(command, "search_book") == 0)
        {
            SearchBookMain(T1, inputFile, outputFile);
        }
        else if(strcmp(command, "list_author") == 0)
        {
            ListAuthor(T2, inputFile, outputFile);
        }
        else if(strcmp(command, "search_by_author") == 0)
        {
            SearchByAuthor(T2, inputFile, outputFile);
        }
        else if(strcmp(command, "delete_book") == 0)
        {
            DeleteBook(&T1, &T2, inputFile, outputFile);
        }
    }
    
    //FreeAllBooks(allBooksInfo, nrBooks);
    DeleteTrie(&T1, 1, FreeBook);
    DeleteTrie(&T2, 2, NULL);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

void DeleteBook(TrieNodePointer *T1, TrieNodePointer *T2, FILE *inputFile, FILE *outputFile)
{
    fgetc(inputFile); // get the space
    char *title = NULL;
    size_t length;

    getline(&title, &length, inputFile); // get the name
    if(title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';

    
    BookPointer searchBook = (BookPointer) SearchTrie(*T1, title);
    // if the book doesnt exist
    if(searchBook == NULL)
    {
        fprintf(outputFile, "Cartea %s nu exista in recomandarile tale.\n", title);
        free(title);
        return;
    }

    char *author = malloc(MAX_AUTHOR);
    strcpy(author, searchBook->author);

    // remove the book from T1 and free the info
    Remove(T1, title, 0, FreeBook);
    
    int found = 0;
    // remove the book from the authors trie
    // and delete the author if it has no books left
    RemoveBookFromAuthor(T2, T2, title, author ,&found);

    free(author);
    free(title);
}

void RemoveBookFromAuthor(TrieNodePointer *T2, TrieNodePointer *OriginalT2, char *title,
                             char *author,int *found)
{
    if(*T2 == NULL)
        return;
    if((*T2)->isEnd && (*T2)->endPointer != NULL)
    {
        // we found the pointer to the books

        // search for the book
        BookPointer book = (BookPointer) SearchTrie((*T2)->endPointer, title);

        // if it exits
        if(book != NULL)
        {
            *found = 1;
            // remove the book and free the info
            Remove((TrieNodePointer *) &((*T2)->endPointer), title, 0, NULL);

            // if there are no more books
            if((*T2)->endPointer == NULL)
            {
                Remove(OriginalT2, author, 0, NULL);
            }
            return;
        }
    }

    int i;
    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((*T2) && (*T2)->sons[i])
        {
            RemoveBookFromAuthor(&(*T2)->sons[i], OriginalT2, title, author, found);
        }

        if(*found == 1)
            return;
    }
}

void ListAuthor(TrieNodePointer T2, FILE *inputFile, FILE *outputFile)
{
    fgetc(inputFile); // get the space
    char *authorName = NULL;
    size_t length;

    getline(&authorName, &length, inputFile); // get the name
    if(authorName[strlen(authorName) - 1] == '\n')
        authorName[strlen(authorName) - 1] = '\0';

    if(authorName[strlen(authorName) - 1] == '~')
    {
        // need to autocomplete
        // delete the ~
        authorName[strlen(authorName) - 1] = '\0';
        AutoCompleteAuthors(T2, authorName, outputFile);
    }
    else
    {
        TrieNodePointer currentBooks = SearchTrie(T2, authorName);

        // if the author exists in the trie
        if(currentBooks != NULL)
        {
            DisplayBooksByAuthor(currentBooks, outputFile);
        }
        else
            fprintf(outputFile,"Autorul %s nu face parte din recomandarile tale.\n", authorName);
    }
    free(authorName);
}

// With a DFS approach print all the books in the trie
void DisplayBooksByAuthor(TrieNodePointer trie, FILE *outputile)
{
    if(trie == NULL)
        return;
    if(trie->isEnd)
        fprintf(outputile,"%s\n", ((BookPointer)trie->endPointer)->title);
    
    int i;
    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((trie)->sons[i])
        {
            DisplayBooksByAuthor(trie->sons[i], outputile);  
        }
    }
}
void DisplayBooksByAuthorLimit(TrieNodePointer trie, FILE *outputile,
                             int limit, int *current)
{
    if(trie == NULL || *current >= limit)
        return;
    if(trie->isEnd)
    {
        fprintf(outputile,"%s\n", ((BookPointer)trie->endPointer)->title);
        (*current)++;
        if(*current >= limit)
            return;
    }
    int i;
    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((trie)->sons[i])
        {
            DisplayBooksByAuthorLimit(trie->sons[i], outputile, limit, current);  
        }
    }
}

void DisplayAuthorsLimit(TrieNodePointer trie, FILE *outputile,
                                int limit, int *current, char *string)
{
    if(trie == NULL || *current >= limit)
        return;
    if(trie->isEnd)
    {
        fprintf(outputile,"%s\n", string);
        (*current)++;
        if(*current >= limit)
            return;
    }
    int i;
    for(i = 0; i< SIGMA; ++i)
    {
        // if the node exists
        if((trie)->sons[i])
        {
            // create a new string and add the current char to it
            int len = strlen(string);
            string[len] = ALPHABET[i];
            string[len+1] = '\0'; 

            DisplayAuthorsLimit(trie->sons[i], outputile, limit, current, string);  
            
            // delete the char we added previosly
            string[len] = '\0';
        }
    }
}


void SearchBookMain(TrieNodePointer T1, FILE *inputFile, FILE *outputFile)
{
    fgetc(inputFile); // get the space

    char *title = NULL;
    size_t length;

    getline(&title, &length, inputFile); // get the book
    if(title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';

    if(title[strlen(title) - 1] == '~')
    {
        // we need to autocomplete
        title[strlen(title) - 1] = '\0';
        AutoCompleteBooks(T1, title, outputFile);
    }
    else
    {
        SearchBook(title, T1, outputFile);
    }
    free(title);
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

void AutoCompleteBooks(TrieNodePointer node, char *key, FILE *outputFile)
{
    if(node == NULL)
        return;
    TrieNodePointer pointerCrawl = node;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);

        if(!pointerCrawl->sons[currIndex])
        {
            fprintf(outputFile, "Nicio carte gasita.\n");
            return;
        }

        pointerCrawl = pointerCrawl->sons[currIndex];
    }
    // we reached the end of the prefix
    int current = 0;
    DisplayBooksByAuthorLimit(pointerCrawl, outputFile, 3, &current);
}

void AutoCompleteAuthors(TrieNodePointer node, char *key, FILE *outputFile)
{
    if(node == NULL)
        return;
    TrieNodePointer pointerCrawl = node;

    int i;

    for(i = 0; i < strlen(key); ++i)
    {
        int currIndex = GetIndexInAlphabet(key[i]);

        if(!pointerCrawl->sons[currIndex])
        {
            fprintf(outputFile, "Niciun autor gasit.\n");
            return;
        }

        pointerCrawl = pointerCrawl->sons[currIndex];
    }
    // we reached the end of the prefix
    int current = 0;
    DisplayAuthorsLimit(pointerCrawl, outputFile, 3, &current, key);
}

void SearchByAuthor(TrieNodePointer T2, FILE *inputFile, FILE *outputFile)
{
    fgetc(inputFile); // reads the space
    char *line = NULL;
    size_t length = 0;

    getline(&line, &length, inputFile); // gets the line after the command

    if(line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';

    if(line[strlen(line) - 1] == '~')
    {

    }

    char *author, *title;

    author = strtok(line, ":");
    if(author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';

    title = strtok(NULL, ":");
    if(title == NULL)
    {
        // autocompletion author
        // delete the ~
        author[strlen(author) - 1] = '\0';

        AutoCompleteAuthors(T2, author, outputFile);
    }
    else
    {
        int toAutoComplete  = 0;
        if(title[strlen(title) - 1] == '\n')
            title[strlen(title) - 1] = '\0';
        
        if(title[strlen(title) - 1] == '~')
        {
            // autcompletion title
            // delete the ~
            title[strlen(title) - 1] = '\0';
            toAutoComplete = 1;

        }

        // get the books
        TrieNodePointer currentBooks = SearchTrie(T2, author);
        if(currentBooks != NULL)
        {
            // search the book and display information
            if(toAutoComplete == 0)
                SearchBook(title, currentBooks, outputFile);
            else
                AutoCompleteBooks(currentBooks, title, outputFile);
        }
        else
        {
            // then the author doesn't exist
            fprintf(outputFile,"Autorul %s nu face parte din recomandarile tale.\n", author);
        }

    }
    free(line);

}