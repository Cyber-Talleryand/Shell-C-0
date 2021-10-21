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

#ifndef P1_FUNC_H
#define P1_FUNC_H

#define MAX_MID 100
#define MAX_COMM 999
#define MAX_AUX_COMM 20
#define ERR_INT -1
#define ERR_CHAR '$'
#define FIN_COMM "-0"


void limpiar_string(char* string, int c);
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
int ayuda(char *str);
tPosL comando(char *str, tList L);
bool an_comm(tList L, tList *historia);

void sym_link(struct stat stats);

int crear(tList *L);
int crear_x(tList L,bool check);

void an_list(tList* L, void (*function)(struct stat stats, tList *temp,char* name));
int list_fich(tList L);
void list_dir_bottom(struct stat structstat, tList *temp,char* name);
//int list_dir_bottom(tList *p_comm,tList *p_arch);


#endif //P1_FUNC_H
