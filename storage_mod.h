//
// Created by t_hss3 on 17/11/21.
//

#ifndef SHELL_STORAGE_MOD_H
#define SHELL_STORAGE_MOD_H
#include "dynamic_list.h"
#include "commands.h"
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#define MAX_MID 100




int borrar(tList L);
int borrarrec(tList L);
int crear(tList L);
int crear_x(tList L,bool check);
void sym_link();
//char * ConvierteModo (mode_t m, char *permisos);
int list_fich(tList L, tList *temp);
int list_fich(tList L,tList *temp);
int list_dir_up(tList L,tList *temp);
void list_dir_bottom(struct stat structstat, tList *temp, char* name);
void list_dir_bottom(struct stat structstat, tList *temp,char* name);
#endif //SHELL_STORAGE_MOD_H
