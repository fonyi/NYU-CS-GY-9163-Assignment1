#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
    int bucket;
    hashmap_t cursor = NULL;
    int word_size = strlen(word);
    char varword[LENGTH];
    //printf("raw word: %s \n",word);
	
    //return if the word is greater than the max length
    if(word_size > LENGTH){
        return false;
    }
	
    //initialize the holder for the word
    memset(varword, '\0', sizeof(varword));
   
    //set alpha chars to lowercase
    for(int i=0; i<=word_size;i++){
        if (isalpha(word[i])){
            varword[i]=tolower((int)word[i]);
        }
        else{
            varword[i]='\0';
        }   
    }
    
    //trim end of a word
   int j = word_size-1;
   while(!isalpha(varword[j-1]) && ispunct(varword[j])){
      varword[j] = '\0';
      j--;
   }
    if(ispunct(varword[j])){
        varword[j] = '\0';
    }
	 
    //trim front of a word
    while(ispunct(varword[0])){
        memcpy(varword, &varword[1], word_size -1);
    }
    
    printf("check word: %s \n",varword);
    bucket = hash_function(varword);
    cursor = hashtable[bucket];
    //bool test = (cursor == NULL);
    //printf("test %d\n",test);
    //printf("bucket %d\n",bucket);
    
    while(cursor){
        //printf("in the loop!\n");
        
        if(strcmp(varword,cursor -> word)==0){
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
    char line[LENGTH+1];
    int bucket=0;
    hashmap_t current = NULL;
    
    //initialize line buffer
    memset(line, '\0', sizeof(line));
   
    
    //current->next = NULL;
    //initialize hash table
    for(int i=0; i<=HASH_SIZE;i++){
        hashtable[i]=NULL;
    }
	
    FILE *fp = fopen(dictionary, "r");
    //check for empty file
    if(fp == NULL) {
        perror("Unable to open file!");
        fclose(fp);
        return false;
    }

    while (fgets(line, LENGTH+1, fp) != NULL) {
	sscanf(line,"%s",line);
        
	//printf("dict: %s", line);
        /* 
        if(line[strlen(line)-1]=='\n'){
            line[strlen(line)-1]='\0';
        }

        for(int i=0;i<=strlen(line);i++){
            line[i]=tolower(line[i]);
        }
        */
	current = malloc(sizeof(struct node));
	    
        //line[strcspn(line,"\n")]=0;
        
        //strncpy(current->word,line,LENGTH+1);
        //printf("%s: %s %s: %d\n"," Loaded word",current->word,"bucket",bucket);
	if(current != NULL){
	    current -> next = NULL;
	    memset(current -> word, '\0', LENGTH+1);
	    strncpy(current -> word, line, strlen(line));
	    
	    bucket = hash_function(line);
	
            if(hashtable[bucket] == NULL){
                hashtable[bucket] = current;
            }
            else{
                current->next = hashtable[bucket];
                hashtable[bucket] =current;
            }
	}
	else{
	    return false;
	}
        memset(line, '\0', sizeof(line));
	
    }

    fclose(fp);
    return true;
}

int check_words(FILE *fp, hashmap_t hashtable[], char* misspelled[]){
    
    //initialize variables
    int num_misspelled = 0;
    int item_len;
    ssize_t input;
    size_t len = 0;
    char* line = NULL;
    char* item;
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

    while ((input = getline(&line, &len, fp)) !=-1 ){
        
        line[strcspn(line,"\n")] = '\0';
        item = strtok(line, " ");
	    
        while(item !=NULL){
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
            checkword = check_word(item, hashtable);
            //printf("Checked %s and it is %d\n",line, checkword);
            if(!checkword){
                misspelled[num_misspelled] = malloc(strlen(item)+1);
		item_len = strlen(item);
                strncpy(misspelled[num_misspelled],item, item_len+1);
                num_misspelled++;
            }
            item = strtok(NULL, " ");
        }
	free(line);
    }
    //printf("check_words found %i misspelled words\n",num_misspelled);
    //fclose(fp);
    return num_misspelled;
}
