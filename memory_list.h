//
// Created by T_hss3 on 25/10/21.
//

#ifndef SHELL_MEMORY_LIST_H
#define SHELL_MEMORY_LIST_H
#include "func.h"
#define TAM_STR 20
#define MEM_T 0
#define STR_T 1
#define DATE_T 2

enum type_id{mem=0,string=1,date=2};
typedef struct tMemory* MemPos;
typedef MemPos MemList;

typedef struct file{
    char filename[TAM_STR];
    int fd;
}file_str;

typedef union esp_info_archive{
    int key;
    file_str file;
}description;

struct tMemory{
    void* memdir;
    int size;
    time_t time;
    struct tm date;
    enum type_id typeId;
    description info;
    MemPos next;
};

void createEmptyMemoList(MemList *L);
void insertItemMemo(void* item, MemList *L);
MemPos findonlymemory(void* item, MemList L);
MemPos findanydata(void* item, MemList L);
void* getItemMem(MemPos p, MemList L);
void deleteAtPositionMem(MemPos p,MemList *L);
void deleteMemorygroup(MemPos p, MemList *L);
void deleteListMem(MemList L);
#endif //SHELL_MEMORY_LIST_H
