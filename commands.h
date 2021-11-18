//
// Created by T_hss3 on 15/11/21.
//

#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H
#include "dynamic_list.h"
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include "storage_mod.h"
#include <unistd.h>
#include <sys/utsname.h>


#define FIN_COMM "-0"

#define MAX_COMM 999

bool is_comm_void(char* str);
bool is_comm_equals(char* str, char* str2);
void limpiar_string(char* string, int c);
void str_to_cmm(char /* * */str[], tList* comm);
void obt_com(tList* comm);

int autores(char *str);
int fecha(char *str);
int infosis();
int pid(char *str);
int historial(char *str,tList *L);
int carpeta (char str[]);
int getpwd();
tPosL comando(char *str, tList L);
int ayuda(char *str);
void ayuda_comando();
void ayuda_pid();
void ayuda_fecha();
void ayuda_autores();
void ayuda_infosis();
void ayuda_historial();
void ayuda_carpeta();
void ayuda_salir();
void ayuda_crear();
void ayuda_listfich();
void ayuda_listdir();
void ayuda_borrar();
void ayuda_borrarrec();
void ayuda_ayuda();
void an_list(tList* L,tList *temp,void (*function)(struct stat stats, tList *temp, char* name));
void get_parameters(tList *L, tList M);
long str_to_int(char* str, char* rubbish);


#endif //SHELL_COMMANDS_H
