//
// Created by t_hss3 on 18/11/21.
//

#ifndef SHELL_MEMORY_AUX_FUNC_H
#define SHELL_MEMORY_AUX_FUNC_H
#include "memory_list.h"
void deleteFromMemoryShared(long key, MemList *L);
void deleteFromMemoryGeneral(int search, MemList *L);
void deleteFromMemoryMmap(char* filename, MemList *L)
#endif //SHELL_MEMORY_AUX_FUNC_H
