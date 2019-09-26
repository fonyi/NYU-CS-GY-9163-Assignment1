#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
    int bucket;
    char varword[LENGTH+1];
    for(int i=0; i<=strlen(word);i++){
        varword[i]=tolower(word[i]);
    }

    bucket = hash_function(varword);
    node *cursor = hashtable[bucket];
    while(cursor != NULL){
        if(strcmp(word,cursor -> word)==true){
            return true;
        }
        else{
            cursor = cursor->next;
        }
    }
    return false;
}

bool load_dictionary(const char* dictionary, hashmap_t hashtable[]){
    
    //initialize variables
    char line[LENGTH];
    size_t len = 0;
    ssize_t read;
    int bucket;
    FILE *fp = fopen(dictionary, "r");
    
    //initialize hash table
    for(int i=0; i<=HASH_SIZE;i++){
        hashtable[i]=NULL;
    }
    
    //check for empty file
    if(fp == NULL) {
        perror("Unable to open file!");
        return false;
    }

    while (fgets(line, LENGTH, fp)) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        if(line[strlen(line)-1]=='\n'){
            line[strlen(line)-1]='\0';
        }

        for(int i=0;i<=strlen(line);i++){
            line[i]=tolower(line[i]);
        }

        bucket = hash_function(line);

        if(hashtable[bucket] == NULL){
            node *current = malloc(sizeof(node));
            strncpy(current->word,line,LENGTH);
            current->next = NULL;
            hashtable[bucket] = current;
        }
        else{
            node *current = malloc(sizeof(node));
            strncpy(current->word,line,LENGTH);
            current->next = hashtable[bucket];
            hashtable[bucket] =current;
        }
    }
    fclose(fp);
    return true;
}

int check_words(FILE *fp, hashmap_t hashtable[], char* misspelled[]){
    //Check for empty file
    if(fp == NULL) {
    perror("Unable to open file!");
    return false;
    }
    
    int num_misspelled = 0;
    char len[100000];
    char *line = strtok(len," ");
    char delim[] = " ";
    while (fgets(len,100000,fp)) {
        line = strtok(NULL," ");
        while(line !=NULL){
            if(line[strlen(line)-1]=='\n'){
                line[strlen(line)-1]='\0';
            }
            line[strlen(line)]='\0';
            char *clean;
            for(;*line;++line){
                if (!ispunct((unsigned char) *line)){
                    *clean++ = tolower((unsigned char) *line);
                }
            }
            *clean = 0;
            printf("Cleaned: %s\n",clean);
            bool checkword;
            checkword = check_word(clean, hashtable);
            if(!(checkword == false)){
                misspelled[num_misspelled] = malloc(strlen(clean));
                strcpy(misspelled[num_misspelled],clean);
                num_misspelled++;
            }
            line = strtok(NULL, " ");
        }

    }
    printf("check_words found %i misspelled words\n",num_misspelled);
    return num_misspelled;
}