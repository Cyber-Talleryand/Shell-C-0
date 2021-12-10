//
// Created by t_hss3 on 10/12/21.
//

#ifndef SHELL_PROCC_LIST_H
#define SHELL_PROCC_LIST_H
#define SHELL_PROCC_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define PNULL -1
#define PLNULL NULL

typedef struct jobdata{
    id_t pid;
    char* commmandline;
    struct tm time1;
    int status;//running, exitted
    int val;//value of the exit(signal, exit value,...)
}jobdata;

typedef struct job* pidPos;

typedef struct job{
    jobdata data;
    pidPos next;
}job;

typedef pidPos pidList;

void createEmptyListPid (pidList* L);
int count_nodePid(pidList L);
bool createNodePid (pidPos* p);
bool insertItemPid(jobdata pid, pidList* L );

pidPos findItemPid(pid_t pid, pidList L) ;
bool isEmptyListPid(pidList L);
pid_t getItemPid(pidPos p, pidList L);
pidPos firstPid(pidList L);
pidPos lastPid(pidList L);
pidPos previousPid(pidPos p, pidList L);
void deleteListPid(pidList* L);
void print_listPid(pidList L, int i);
void deleteAtPositionPid(pidPos p, pidList *L);
void deleteListPidCond(pidList *L,int comm, int arg, int arg2);



#endif //SHELL_PROCC_LIST_H
