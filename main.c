#include "dictionary.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    int num_misspelled = 0;
    FILE *fp = fopen(argv[1], "r");
    load_dictionary(argv[2], hashtable);
    num_misspelled = check_words(fp, hashtable, misspelled);
    fclose(fp);
    printf("There are %d mistakes in the file.\n",num_misspelled);
}

