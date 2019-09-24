#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
    int bucket;
    int hash_function();
    char * varword = strdup(word);

    bucket = hash_function(word);
    struct node * hashmap[bucket];
    hashmap_t cursor;
    cursor = hashmap[bucket];
    unsigned char *tptr = (unsigned char *)varword;
    while(*tptr){
        *tptr = tolower(*tptr);
        tptr++;
    }
    while(cursor != NULL){
        if(word == cursor -> word){
            return true;
        }
        cursor = cursor->next;
    }
    bucket = hash_function(word);
    cursor = hashmap[bucket];
    while(cursor != NULL){
        if(varword==cursor -> word){
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

bool load_dictionary(const char* dictionary, hashmap_t hashtable[]){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp = fopen(dictionary, "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        return false;
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        hashmap_t new_node;
        new_node -> next = NULL;
        strcpy(new_node -> word,line);
        int bucket = hash_function(line);
        if(hashtable[bucket]==NULL){
            hashtable[bucket] = new_node;
        }
        else{
            new_node -> next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
    }
    fclose(fp);
    return true;
}

int check_words(FILE *fp, hashmap_t hashtable[], char* misspelled[]){
    int num_misspelled = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = " ";
    while ((read = getline(&line, &len, fp)) != -1) {
        char *ptr = strtok(line,delim);
        while(ptr !=NULL){
            size_t pos = 0;
            for (char *p = ptr;*p;++p){
                if (isalpha(*p)){
                    ptr[pos++] = *p;
                }
            ptr[pos] = '\0';
            if(!check_word(ptr,hashtable)){
                char **ptr_ptr =&ptr;
                misspelled = ptr_ptr;
                num_misspelled++;
            }
            }
            ptr = strtok(NULL, delim);
        }

    }
    
    return num_misspelled;
}