//
// Created by T_hss3 on 25/10/21.
//

#include "memory_list.h"
void createEmptyMemoList(MemList *L){
    *L=MNULL;
};
bool isEmptyListMemo(MemList L){
    return L==MNULL;
}
struct tMemory* createItemMemo(long size){
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
    str_memo->typeId=undef;
    //str_memo->info;
    return str_memo;
}

void modifyItem(struct tMemory* item,enum type_id type, description descriptor){
    if(type==memo){
        item->typeId=memo;
    }
    else if(type==shared){
        item->typeId=shared;
        item->info=descriptor;

    }
    else if(type==mmap_id){
        item->typeId=mmap_id;
        item->info=descriptor;
    }
    else item->typeId=undef;
    return;
    //(*item)->info=memo;
}

description createDescriptorShared(int key){
        description descriptor;
        descriptor.key=key;
    return descriptor;
}

description createDescriptormmap(int fd, char* filename){
    description descriptor;
    descriptor.file.fd=fd;
    strcpy(descriptor.file.filename,filename);
    return descriptor;
}


void insertItemMemo(struct tMemory* item, MemList *L){
    MemPos p;
    if(isEmptyListMemo(*L)){
        *L=item;
        return;
    }
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
MemPos prev_mem(MemPos p, MemList L){
    if (L==p || p==MNULL ||isEmptyListMemo(L)){
        return  MNULL;
    }
    else{
        MemPos q;
        for (q=L;q->next!=p;q=q->next);
        return q;
    }
}

void deleteAtPositionMemo(MemPos p,MemList *L){
    MemPos m,temp;
    if(p==MNULL) return;
    if(prev_mem(p,*L)==MNULL){
        (*L)=(*L)->next;
    }
    else prev_mem(p,*L)->next=p->next;
    free(p->memdir);
    free(p);
};



void deleteListMemo(MemList *L){
    MemPos p;
    while(*L!=MNULL){
        p=*L;
        *L=(*L)->next;
        free(p->memdir);
        free(p);
    }
};
void print_memory_list(MemList L){
    MemPos p;
    for(p=L;p!=MNULL;p=p->next){
        if(p->typeId==memo) printf("%p: size: %ld malloc on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                   p->date.tm_mday, p->date.tm_mon, p->date.tm_year + 1900,p->date.tm_hour,
                                   p->date.tm_min, p->date.tm_sec);
        if(p->typeId==mmap_id)printf("%p: size: %ld mmap %s (fd:%i) on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                     p->info.file.filename, p->info.file.fd, p->date.tm_mday, p->date.tm_mon,
                                     p->date.tm_year + 1900,p->date.tm_hour, p->date.tm_min, p->date.tm_sec);
        if(p->typeId==shared)printf("%p: size: %ld shared memory key %i on: %d-%d-%d %d:%d:%d, \n",p->memdir,p->size,
                                    p->info.key, p->date.tm_mday, p->date.tm_mon, p->date.tm_year + 1900,
                                    p->date.tm_hour, p->date.tm_min, p->date.tm_sec);
    }

}