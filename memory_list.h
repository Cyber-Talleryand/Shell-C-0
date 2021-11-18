//
// Created by T_hss3 on 25/10/21.
//

#ifndef SHELL_MEMORY_LIST_H
#define SHELL_MEMORY_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define TAM_STR 20
#define MEM_T 0
#define STR_T 1
#define DATE_T 2
#define MNULL NULL

enum type_id{undef=0,memo=1,mmap_id=2,shared=3};
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
    long size;
    time_t time;
    struct tm date;
    enum type_id typeId;
    description info;
    MemPos next;
};

void createEmptyMemoList(MemList *L);
bool isEmptyListMemo(MemList L);
void insertItemMemo(struct tMemory* item, MemList *L);
MemPos findDirMemo(void* item, MemList L);
MemPos findSizeMemo(long size, MemList L);
MemPos findItemMemo(void* item, MemList L);
void* getItemMemo(MemPos p, MemList L);
void deleteAtPositionMemo(MemPos p,MemList *L);
void deleteMemorygroup(MemPos p, MemList *L);
void deleteListMemo(MemList *L);
struct tMemory* createItemMemo(long size);
void print_memory_list(MemList L);
void modifyItem(struct tMemory* item,enum type_id type, description descriptor);
description createDescriptorShared(int key);
description createDescriptormmap(int fd, char* filename);
#endif //SHELL_MEMORY_LIST_H
