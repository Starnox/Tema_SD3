/* MIHAILESCU Eduard-Florin - 312CB */
#include "utils.h"

// get the position in the alphabet
int GetIndexInAlphabet(char c)
{
    int i;
    for(i = 0; i < SIGMA; ++i)
    {
        if(c == ALPHABET[i])
            return i;
    }

    return -1; // the character is not in the alphabet
}