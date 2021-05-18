# Tema 3 SD
## Elev: Mihailescu Eduard-Florin
## Grupa: 312CB

### Descriere generala
Acest cod are ca scop rezolvarea temei 3 propusa in cadrul cursului de Structuri de date(SD)
din anul I, seria CB de la Facultatea de Automatica si Calculatoare. Comentarile pentru
cod sunt scrise in limba engleza in vederea antrenarii acestui skill si pentru o potentiala
incarcare pe github la finalul anului. Specific faptul ca tema a obtinut un punctaj maxim
la rularea locala (135/135 si 20/20);

### Structura
Codul este impartit in 3 fisiere surs (.c) si 3 fisiere header (.h) aferente.
Astfel in:
*   `TTrie.c` - se regaseste implementarea structurii trie
    -   Initializare -> `InitialiseTrieNode()`
    -   Inserare nod nou -> `InsertNode()`
    -   Cautare nod -> `SearchTrie()`
    -   Verificare nod gol -> `SearchTrie()`
    -   Eliberare memorie trie -> `DeleteTrie()`
    -   Stergere nod specific -> `Remove()`

*   `utils.c` - se regasesc constante importante si o functie ajutatoare
    -   Constante:
            - ALPHABET -> string cu alfabetul dat
            - SIGMA -> numarul de caractere din alfabet
            - MAX_BOOK -> numarul maxim de caractere al unei carti
            - MAX_AUTHOR -> numarul maxim de caractere al unui autor
    -   Functie aflat indexul unui caracter in alfabet -> `GetIndexInAlphabet()`

*   `tema3.c` -> fisierul in care se afla functia main si functile de baza
                 ale programului
    -   Citeste carte noua ->   `ReadBook()`
    -   Afisare carti scrise de un autor dat -> `DisplayBooksByAuthor()`
    -   Afisare nr limitat de carti scrise de un autor dat -> `DisplayBooksByAuthorLimit()`
    -   Afisare nr limitat de autori -> `DisplayAuthorsLimit()`
    -   Cautare dupa autor -> `SearchByAuthor()`
    -   Functia care asigura prelucrarea comenzii 'search_book' -> `SearchBookMain()`
    -   Functia de autocompletare carti -> `AutoCompleteBooks()`
    -   Functie de autocompletare autori -> `AutoCompleteAuthors()`
    -   Functie care afiseaza cartile unui autor -> `ListAuthor()`
    -   Functia care asigura prelucrarea comenzii 'delete_book' -> `DeleteBook()`
    -   Functie care sterge o carte din tria corespunzatoare 
    unui autor -> `RemoveBookFromAuthor()`
