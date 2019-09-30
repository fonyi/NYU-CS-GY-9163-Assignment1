#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
    int bucket;
    int word_size = strnlen(word,LENGTH);
    char varword[word_size];
    //printf("raw word: %s \n",word);
    for(int i=0; i<=word_size;i++){
        if (!ispunct((unsigned char)word[i])){
            varword[i]=tolower(word[i]);
        }
        else{
            varword[i]='\0';
        }   
    }
   
    //printf("check word: %s \n",varword);
    bucket = hash_function(varword);
    node* cursor = hashtable[bucket];
    //bool test = (cursor == NULL);
    //printf("test %d\n",test);
    //printf("bucket %d\n",bucket);
    
    while(cursor){
        //printf("in the loop!\n");
        
        if(strncmp(varword,cursor -> word,LENGTH+1)==0){
            //printf("Valid word! %s and %s\n",varword,cursor->word);
            return true;
            
        }
        else{
            //printf("Invalid word! %s and %s\n",varword,cursor->word);
            cursor = cursor->next;
            
        }
    }
    return false;
}

bool load_dictionary(const char* dictionary, hashmap_t hashtable[]){
    
    //initialize variables
    char line[LENGTH];
    int bucket=0;
    FILE *fp = fopen(dictionary, "r");
   
    node* current = malloc(100000*sizeof(node));
    current->next = NULL;
    //initialize hash table
    for(int i=0; i<=HASH_SIZE;i++){
        hashtable[i]=NULL;
    }
    
    //check for empty file
    if(fp == NULL) {
        perror("Unable to open file!");
        fclose(fp);
        return false;
    }

    while (fgets(line, LENGTH, fp) != NULL) {

        //printf("dict: %s", line);
        /* 
        if(line[strlen(line)-1]=='\n'){
            line[strlen(line)-1]='\0';
        }

        for(int i=0;i<=strlen(line);i++){
            line[i]=tolower(line[i]);
        }
        */
        line[strcspn(line,"\n")]=0;
        bucket = hash_function(line);
        strncpy(current->word,line,LENGTH+1);
        //printf("%s: %s %s: %d\n"," Loaded word",current->word,"bucket",bucket);
        if(hashtable[bucket] == NULL){
            hashtable[bucket] = current;
        }
        else{
            current->next = hashtable[bucket];
            hashtable[bucket] =current;
        }
        current = malloc(sizeof(node));
        current -> next = NULL;
	
    }
    free(current);
    fclose(fp);
    return true;
}

int check_words(FILE *fp, hashmap_t hashtable[], char* misspelled[]){
    
    //initialize variables
    int num_misspelled = 0;
    char len[500000];
    char* line;
    //line = strtok(len," ");
    
    //Check for empty file
    if(fp == NULL) {
    perror("Unable to open file!");
    fclose(fp);
    return false;
    }
    for(int i=0; i < MAX_MISSPELLED; i++){
        misspelled[i] = NULL;
    }

    while (fgets(len,100000,fp)) {
        
        line = strtok(len," ");
        //line = strtok(NULL," ");
        while(line !=NULL){
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
            bool checkword;
            checkword = check_word(line, hashtable);
            //printf("Checked %s and it is %d\n",line, checkword);
            if(!checkword){
                misspelled[num_misspelled] = malloc(sizeof(char)*strlen(line)+1);
                strcpy(misspelled[num_misspelled],line);
                num_misspelled++;
 		free(misspelled[num_misspelled]);
            }
            line = strtok(NULL, " ");
	    free(misspelled[num_misspelled]);
            
        }

    }
    //printf("check_words found %i misspelled words\n",num_misspelled);
    //fclose(fp);
    return num_misspelled;
}