//
// Created by talleryandghosthss3uro on 27/9/21.
//
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include "dynamic_list.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <sys/mman.h>

#include <sys/wait.h>
#include <sys/shm.h>
#include "memory_list.h"
#include "commands.h"
#include "memory_list.h"



#ifndef P1_FUNC_H
#define P1_FUNC_H

#define MAX_MID 100
#define MAX_AUX_COMM 20
#define ERR_INT -1
#define ERR_CHAR '$'
#define _POSIX_SOURCE
#define LEERCOMPLETO ((ssize_t)-1)


void limpiar_string(char* string, int c);
bool is_comm_void(char* str);
void ayuda_ayuda();
void obt_com(tList* comm);
int getpwd();
int autores(char *str);
int fecha(char *str);
int pid(char *str);
int carpeta (char str[]);
int historial(char *str,tList *L);
int infosis();
int historial(char *str,tList *L);
int borrar(tList L);
int borrarrec(tList L);
void ayuda_comando();
void ayuda_pid();
void ayuda_fecha();
void ayuda_autores();
void ayuda_infosis();
void ayuda_historial();
void ayuda_carpeta();
void ayuda_autores();
void ayuda_salir();
void ayuda_crear();
void ayuda_listfich();
void ayuda_listdir();
void ayuda_borrar();
void ayuda_borrarrec();
int ayuda(char *str);
tPosL comando(char *str, tList L);
bool an_comm(tList L, tList *historia, tList *dynamic_memory,bool check);

void sym_link();

int crear(tList L);
int crear_x(tList L,bool check);

void an_list(tList* L,tList *temp,void (*function)(struct stat stats, tList *temp, char* name));
int list_fich(tList L,tList *temp);
int list_dir_up(tList L,tList *temp);
void list_dir_bottom(struct stat structstat, tList *temp, char* name);
//int list_dir_bottom(tList *p_comm,tList *p_arch);

ssize_t LeerFichero (char *fich, void *p, ssize_t n);
void * MmapFichero (char * fichero, int protection);
void Mmap (char *str, char* str2, char *fich);
void * ObtenerMemoriaShmget (key_t clave, size_t tam);


#endif //P1_FUNC_H
