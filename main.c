#include "dictionary.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen(argv[1], "r");
    load_dictionary(argv[0], hashtable);
    int num_misspelled = check_words(fp, hashtable, misspelled);
    printf("There are %d mistakes in the files.",num_misspelled);
}

