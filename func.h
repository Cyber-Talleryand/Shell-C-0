//
// Created by talleryandghosthss3uro on 27/9/21.
//

#ifndef P1_FUNC_H
#define P1_FUNC_H

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

int crear_x(tList L);


#endif //P1_FUNC_H
