#include "dictionary.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void printMisspelled(char* misspelled[]) {
    int i;
    for(i = 0; i < MAX_MISSPELLED; i++) {
        if(misspelled[i] != NULL) {
            printf("Incorrect: %s \n", misspelled[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    int num_misspelled = 0;
    char *dict = argv[2];
    char *file = argv[1];
    FILE *fp = fopen(file, "r");
    load_dictionary(dict, hashtable);
    num_misspelled = check_words(fp, hashtable, misspelled);
    fclose(fp);
    printf("There are %d mistakes in the file.\n",num_misspelled);
    printMisspelled();
}

