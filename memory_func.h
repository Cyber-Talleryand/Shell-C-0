//
// Created by t_hss3 on 17/11/21.
//

#ifndef SHELL_MEMORY_FUNC_H
#define SHELL_MEMORY_FUNC_H
#include "storage_mod.h"
//#include "dynamic_list.h"
#include "memory_list.h"
#include "commands.h"
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "memory_aux_func.h"

#define MAX_AUX_COMM 20
#define LEERCOMPLETO ((ssize_t)-1)
#define TAMANO 4096


ssize_t LeerFichero (char *fich, void *p, ssize_t n);
void * MmapFichero (char * fichero, int protection,MemList *L);
void Mmap (char *str, char* str2, char *fich, MemList *L);
void * ObtenerMemoriaShmget (key_t clave, size_t tam, MemList* L);
long str_to_int_base(char* str, char* rubbish, int base);
void dealloc(char *str, tList *memo, MemList* L);
void malloc_general(char *str, char *size, MemList *dynamic_register);
void main_shared(char* str,char* key, char* tam, MemList* L);
bool SharedCreate (char *str, char *str2,MemList* L);
void doRecursiva (char *n);
void recursiva_bottom(int n);
#endif //SHELL_MEMORY_FUNC_H
