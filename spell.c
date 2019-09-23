#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"

bool check_word(const char* word, hashmap_t hashtable[]){
int bucket;
int hash_function();
const char* lower_case();
bucket = hash_function(word);
struct node * hashmap[bucket];
hashmap_t cursor;
cursor = hashmap[bucket];
while(cursor != NULL){
    if(word == cursor -> word){
        return true;
    }
    cursor = cursor->next;
}
bucket = hash_function(word);
cursor = hashmap[bucket];
while(cursor != NULL){
    if(lower_case(word)==cursor->word){
        return true;
    }
    cursor = cursor->next;
}
return false;
}

bool load_dictionary(const char* dictionary, hashmap_t hashtable[]){
return true;
}

int check_words(FILE *fp, hashmap_t hashtable[], char* misspelled[]){
int num_misspelled = 0;
int ch = getc(fp);
while(ch != EOF){

}
return num_misspelled;
}