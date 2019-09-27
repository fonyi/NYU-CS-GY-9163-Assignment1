#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
    int bucket;
    char varword[LENGTH+1];
    printf("raw word: %s \n",word);
    for(int i=0; i<=strlen(word);i++){
        if (!ispunct(word[i])){
            varword[i]=tolower(word[i]);
        }   
    }
    printf("check word: %s \n",varword);
    bucket = hash_function(varword);
    node *cursor = hashtable[bucket];
    while(cursor != NULL){
        //printf("Word:%s Cursor:%s",word,cursor->word);
        if(strcmp(varword,cursor -> word)==true){
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
    
    //initialize variables
    int num_misspelled = 0;
    char len[100000];
    char* line = strtok(len," ");
    
    //Check for empty file
    if(fp == NULL) {
    perror("Unable to open file!");
    return false;
    }
    for(int i=0; i < MAX_MISSPELLED; i++){
        misspelled[i] = NULL;
    }

    while (fgets(len,100000,fp)) {
        printf("Line: %s\n",len);
        line = strtok(len," ");
        //printf("Word: %s\n",line);
        //line = strtok(NULL," ");
        while(line !=NULL){
            //printf("in while %s",line);
            /*
            if(line[strlen(line)-1]=='\n'){
                line[strlen(line)-1]='\0';
                printf("%s",line);
            }
            line[strlen(line)]='\0';
            char *clean = 0;
            for(;*line;++line){
                if (isalpha((unsigned char) *line)){
                    *clean++ = *line;
                    printf("clean: %s",clean);
                }
            }
            */
            //*clean = 0;
            //printf("Cleaned: %s\n",clean);
            bool checkword;
            checkword = check_word(line, hashtable);
            if(!(checkword == false)){
                misspelled[num_misspelled] = malloc(strlen(line));
                strcpy(misspelled[num_misspelled],line);
                num_misspelled++;
            }
            line = strtok(NULL, " ");
        }

    }
    printf("check_words found %i misspelled words\n",num_misspelled);
    return num_misspelled;
}