//
// Created by talleryandghosthss3uro on 27/9/21.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "memory_list.h"
#include "commands.h"
#include "memory_func.h"
#include "storage_mod.h"
#include "process.h"



#ifndef P1_FUNC_H
#define P1_FUNC_H


#define MAX_AUX_COMM 20
#define LEERCOMPLETO ((ssize_t)-1)

bool an_comm(tList L, tList *historia, MemList *dynamic_memory, pidList *PL, bool check);


#endif //P1_FUNC_H
