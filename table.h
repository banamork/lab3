#ifndef __TABLE_H__
#define __TABLE_H__

typedef struct KeySpace2 {
    int busy;
    char* key;
    char* info;
} KeySpace2;

typedef struct Table {
    int msize;
    int asize;
    KeySpace2* ks2;
} Table;


char* check(char* choice);
int getInt(char* str);
Table* makeTable(Table* table, int size);
int h1(char *key, int size);
int h2(char* key, int size);
int push(Table* table, char* key, char* info);
Table* freeTable(Table* table);
KeySpace2* search(Table* table, char* key);
int deleteByKey(Table* table, char* key);
void printTable(Table* table);

#endif //TABLE_H__