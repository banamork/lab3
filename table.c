#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "table.h"


char* check(char* choice) {
    while(1) {
        if(choice == NULL || strlen(choice) == 0) {
            choice = readline("Ничего не введено. \n");
        } else if(strlen(choice) > 1) {
            free(choice);
            choice = readline("Неверно введён пункт меню. \n");
        } else if(choice[0] < '0' || choice[0] > '4') {
            free(choice);
            choice = readline("Неверно введён пункт меню. \n");
        } else {
            break;
        }
    }
    return choice;
}


int getInt(char* str) {
    while(1) {
        if(str == NULL || strlen(str) == 0) {
            str = readline("Ничего не введено. \n");
        } else {
            int flag = 0;
            for(int i = 0; i < strlen(str); i++) {
                if(!isdigit(str[i])) {
                    flag = 1;
                    break;
                }
            }
            if(flag) {
                free(str);
                str = readline("Введено не целое число. \n");
            } else {
                int result = atoi(str);
                return result;
            }
        }
    }
}


Table* makeTable(Table* table, int size) {
    table = (Table*) calloc(1, sizeof(Table));
    table->msize = size;
    table->ks2 = (KeySpace2*) calloc(size, sizeof(KeySpace2));
    table->asize = 0;
    return table;
}


int hash1(char *key, int size) {
    int hash = 6452;
    int k = 0;
    while (k = *key++) {
        hash = ((hash << 6) + hash) + k;
    }  
    hash = hash % size;
    hash = abs(hash);
    return hash;
}


int hash2(char* key, int size) {
    int hashsum = 0;
    for(int i = 0; i < strlen(key); i++) {
        hashsum = hashsum * 32 + key[i];
    }
    int prime = size - 1;
    int index = prime - (hashsum % prime);
    return index;
}


int push(Table* table, char* key, char* info) {
    if(table->msize == table->asize) {
        return 1;
    }
    int st = 0;
    int i = 0;
    int j = 1;
    i = st = hash1(key, table->msize);
    while((table->ks2[i].busy > 0) && (j < table->msize)) {
        if(strcmp(table->ks2[i].key, key) == 0){
            return 2;
        }
        i = (st + j * (hash2(key, table->msize))) % table->msize;
        j++;
    }
    table->ks2[i].info = (char*)calloc(strlen(info) + 1, sizeof(char));
    strcpy(table->ks2[i].info, info);
    table->ks2[i].key = (char*)calloc(strlen(key) + 1, sizeof(char));
    strcpy(table->ks2[i].key, key);
    table->ks2[i].busy = 1;
    table->asize = table->asize + 1;
    return 0;
}


Table* freeTable(Table* table) {
    int i = 0;
    int j = 0;
    while(j < table->asize) {
        if(table->ks2[i].busy > 0) {
            free(table->ks2[i].info);
            free(table->ks2[i].key);
            j++;
        }
        i++;
    }
    free(table->ks2);
    free(table);
    table = NULL;
    return table;
}


KeySpace2* search(Table* table, char* key) {
    KeySpace2* searched = NULL;
    int i = 0;
    int j = 0;
    while(j < table->asize){
        if(table->ks2[i].busy > 0){
            if(strcmp(table->ks2[i].key, key) == 0){
                searched = (KeySpace2*) calloc(1, sizeof(KeySpace2));
                searched->info = (char*) calloc(strlen(table->ks2[i].info) + 1, sizeof(char));
                strcpy(searched->info, table->ks2[i].info);
                searched->key = (char*)calloc(strlen(table->ks2[i].key) + 1, sizeof(char));
                strcpy(searched->key, table->ks2[i].key);
                break;
            }
            j++;
        }
        i++;
    }
    return searched;
}


int deleteByKey(Table* table, char* key) {
     int i = 0;
    int j = 0;
    int f = 0;
    while(j < table->asize) {
        if(table->ks2[i].busy > 0) {
            if(strcmp(table->ks2[i].key, key) == 0) {
                free(table->ks2[i].key);
                free(table->ks2[i].info);
                table->ks2[i].busy = 0;
                f = 1;
                break;
            }
            j++;
        }
        i++;
    }
    table->asize = table->asize - 1;
    if(f) {
        return 0;
    } else {
        return 1;
    }
}


void printTable(Table* table) {
    int i = 0;
    int j = 0;
    while(j < table->asize){
        if(table->ks2[i].busy > 0){
            printf(" %d) | %s | %s \n", i, table->ks2[i].key, table->ks2[i].info);
            j++;
        }
        i++;
    }
}