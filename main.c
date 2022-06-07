#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline/readline.h"
#include "table.h"


int main() {
    int flag = 1;
    Table* table = NULL;
    while(flag) {
        printf("Выберите действие: \n");
        printf("0 - Выйти из программы.\n");
        printf("1 - Вставить элемент в таблицу. \n");
        printf("2 - Поиск в таблице элемента по ключу. \n");
        printf("3 - Удаление из таблицы элемента по ключу. \n");
        printf("4 - Вывод содержимого таблицы на экран. \n");
        char* choice = readline("");
        choice = check(choice);
        switch(choice[0]) {
            case '0':
                flag = 0;
                if(table != NULL) {
                    table = freeTable(table);
                }
                break;
            case '1':
                if(table == NULL) {
                    char* s = readline("Введите размер таблицы. \n");
                    int size = getInt(s);
                    free(s);
                    table = makeTable(table, size);
                }
                char* key = readline("Введите ключ. \n");
                char* info = readline("Введите информацию. \n");
                int f1 = push(table, key, info);
                if(f1 == 1) {
                    printf("Таблица переполнена. \n");
                } else if(f1 == 2) {
                    printf("Элемент с таким ключом уже существует. \n");
                }
                free(key);
                free(info);
                break;
            case '2':
                if(table == NULL) {
                    printf("Таблица не введена. \n");
                    break;
                }
                key = readline("Введите ключ для поиска элемента. \n");
                KeySpace2* searched = search(table, key);
                if (searched == NULL) {
                    printf("Эелемент не найден. \n");
                } else {
                    printf("key --> %s\n", searched->key);
                    printf("info --> %s\n", searched->info);
                }
                free(searched->key);
                free(searched->info);
                free(searched);
                break;
            case '3':
                if(table == NULL) {
                    printf("Таблица не введена. \n");
                    break;
                }
                key = readline("Введите ключ для удаления элемента. \n");
                int del_status = deleteByKey(table, key);
                if(del_status) {
                    printf("Элемент с таким ключом не найден. \n");
                } else {
                    printf("Элемент с таким ключом успешно удалён. \n");
                }
                free(key);
                break;
            case '4':
                if(table == NULL) {
                    printf("Таблица не введена. \n");
                    break;
                }
                printTable(table);
                break;
            default:
                break;
        }
        free(choice);
    }
    

    return 0;
}