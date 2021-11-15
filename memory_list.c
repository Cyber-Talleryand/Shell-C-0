//
// Created by T_hss3 on 25/10/21.
//

#include "memory_list.h"
void createEmptyMemoList(MemList *L){
    *L=MNULL;
};
MemPos* createItemMemo(long size){
    time_t t;
    void* alpha;
    struct tMemory* str_memo=malloc(sizeof(struct tMemory));
    struct tm tm = *localtime(&t);
    alpha= malloc(size);
    str_memo->memdir=alpha;
    str_memo->date=tm;
    str_memo->size=size;
    str_memo->typeId=undef;
    str_memo->next=MNULL;
    //str_memo->info;
    return str_memo;

}

void insertItemMemo(void* item, MemList *L){
    MemPos p;
    if(isEmptyListMemo(*L))*L=item;
    for(p=*L;p->next!=NULL;p=p->next);
    p->next=item;
};

MemPos findDirMemo(void* item, MemList L){
    MemPos p;
    for(p=L;p!=MNULL && p->memdir!=item;p=p->next);
    if(p->memdir==item) return p;
    return MNULL;
};
MemPos findItemMemo(void* item, MemList L){

}
MemPos findSizeMemo(long size, MemList L){
    MemPos p;
    for(p=L;p!=MNULL && p->size!=size;p=p->next);
    if(p->size==size) return p;
    return MNULL;
}
void* getItemMemo(MemPos p, MemList L) {
    return p;
}
void deleteAtPositionMemo(MemPos p,MemList *L){
    MemPos m,temp;
    for(m=*L;m!=MNULL && m->next->memdir!=p->memdir;m=m->next);
    if(m->next->memdir==p->memdir){
        temp=m->next;
        m->next=p->next;
        free(p->memdir);
        free(temp);
    }
};

void deleteMemorygroup(MemPos p, MemList *L);
void deleteListMemo(MemList *L){
    MemPos p;
    while(*L!=MNULL){
        p=*L;
        *L=(*L)->next;
        free(p);
    }
};
void print_memory_list(MemList *L){
    MemPos p;
    for(p=L;p!=MNULL;p=p->next){
        if(p->typeId==memo) printf("%p: size: %ld malloc on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                   p->date.tm_mday, p->date.tm_mon, p->date.tm_year + 1900,p->date.tm_hour,
                                   p->date.tm_min, p->date.tm_sec);
        if(p->typeId==mmap_id)printf("%p: size: %ld mmap %s (fd:%i) on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                     p->info.file.filename, p->info.file.fd, p->date.tm_mday, p->date.tm_mon,
                                     p->date.tm_year + 1900,p->date.tm_hour, p->date.tm_min, p->date.tm_sec);
        if(p->typeId==shared)printf("%p: size: %ld shared memory key %i on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                    p->info.file.fd, p->date.tm_mday, p->date.tm_mon, p->date.tm_year + 1900,
                                    p->date.tm_hour, p->date.tm_min, p->date.tm_sec);
    }

}