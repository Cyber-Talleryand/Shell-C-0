//
// Created by t_hss3 on 29/11/21.
//

#ifndef SHELL_PROCC_LIST_H
#define SHELL_PROCC_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PNULL -1
#define PLNULL NULL
typedef struct t_Pid* pidPos;

typedef pidPos pidList;

struct t_Pid{
    pid_t proccess;
    pidPos next;
};

void createEmptyListPid (pidList* L);
int count_nodePid(pidList L);
bool createNodePid (pidPos* p);
bool insertItemPid(pid_t pid, pidList* L );
pidPos findItemPid(pid_t pid, pidList L) ;
bool isEmptyListPid(pidList L);
pid_t getItemPid(pidPos p, pidList L);
pidPos firstPid(pidList L);
pidPos lastPid(pidList L);
pidPos previousPid(pidPos p, pidList L);
void deleteListPid(pidList* L);
void print_listPid(pidList L,int i);
void deleteAtPositionPid(pidPos p, pidList *L);


#endif //SHELL_PROCC_LIST_H
