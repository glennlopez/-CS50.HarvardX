#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const unsigned int N = 26; // size of bucket

unsigned int hash(const char *word);

int main ()
{
    printf("hash: %i\n", hash("baby"));
    return 0;
}

// STEP 2. Hashes word to a number - Take a word and run a hash function on it, returning some number that coresponds with the word
unsigned int hash(const char *word)
{                               //1   2   3   4   5   6   7   8   9   10  1   2   3   4   5   6   7   8   9   20  1   2   3   4   5   6
    const char alphadex[] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int indexSum = 0;

    int i;
    for (int j = 0; word[j] != '\0'; j++)
    {
        i = 0;
        while (alphadex[i] != word[j])
        {
            i++;
            if (alphadex[i] == word[j])
            {
                indexSum += i;
                continue;
            }
        }
    }

    return indexSum % N;
}
