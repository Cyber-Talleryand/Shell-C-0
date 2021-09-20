/*Cosas que quedan por hacer
 *
 * ayuda[cmd}
 * Implementacion listas -> Historial
 * Carpeta
 * Comprobar que se cumples las condiciones iniciales del bucle (son 5)
 * */
/*
 * Dudas: Es necesario que los comandos y los argumentos sean procesados en el bucle principal?
 * Es necesario que se cunpla el orden de ejecucion propuesto en el bucle?
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
//#include "dynamic_list.h"


#define MAX_COMM 600
#define ERR_INT -1
#define ERR_CHAR '$'

//Vamos a definir una estructura variable para almacenar un numero ilimitado de comandos


void obt_com(char *an_str) {
    char c;
    bool status;
    int i = 0;
    printf("\n>>");
    do {
        c = getchar();
        if (i >= MAX_COMM && (c == EOF || c == '\n')) {
            status = false;
            an_str[i] = '\0';
        } else {
            an_str[i] = c;
            i++;
        }
    } while (status);

}


int search_arg(char *an_str){
    int i;
    for(i=0;i<MAX_COMM && an_str[i]!=' ';i++);
    if(i==0) return 0;
    else if(i<MAX_COMM && i>0 && an_str[i+1]!=' ')return i;
    else return ERR_INT;
}
/*
//Usar wordcounter para implementar esta función correctamente
int search_next_arg(char *an_str, int f){
    int i;
    for(i=f;i<MAX_COMM && an_str[i]!=' ';i++);
    if(i<MAX_COMM)return i;
    else return ERR_INT;
}
*/
void exact_comm(char *an_str,char *dev){
    int i,cont;
    for(i=0;i<MAX_COMM && an_str[i]!=' ';i++);
    for(cont=0;cont<=i;cont++){
        dev[cont]=an_str[cont];
    }
}
char exact_arg(char *an_str,int i){
    if(i==ERR_INT) return ERR_CHAR;
    if(an_str[i]==' ') i++;
    if(an_str[i]=='-') i++;
    return an_str[i];
}

bool getpwd(char* cwd){
    char aux;
        getcwd(&aux,sizeof(cwd));
        strcpy(cwd,&aux);
        return 0;
}



void autores(char *str){
    int i; char aux;
    i=search_arg(str);aux= exact_arg(str,i);
    if (aux!='l') printf("Rodrigo Dantes Gonzalez Mantuano");
    if (aux!='n') printf("r.d.gmantuano@udc.es");
}

int fecha(){
    printf("%d", system("date"));
    return 0;
}

int infosis(){
    struct utsname aux;
    uname(&aux);
    printf("%s",aux.sysname);
    return 0;
}

int pid(char *str){
    int i; char aux;
    pid_t process_id;
    i=search_arg(str);aux=exact_arg(str,i);
    if(aux=='p')    printf("Parent_PID Terminal: %d\n",getppid());
    else if (aux==ERR_CHAR) printf("Argument incorrect (check the documentation)");
    else printf("PID Terminal: %d\n",getpid());


    return 0;

}
//Todo finalizado hasta aquí
/*
int carpeta (char PATH){

    if(PATH exists)return chdir(PATH);
    else if(getpwd(&PATH)) chdir(PATH);
    else{
        printf("Unexpeted error, Path not found pr dissappeared");
        return 5;
    }

}
*/

//obtiene




//La funcion devuelve el directorio actual de ejecucion del terminal
//Devuelve el tamaño des string en palabras
int TrocearCadena(char * cadena, char ** trozos){
    int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL) return 0;
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) i++;
    return i;
}

int main(){
    char c,comm[MAX_COMM];


    char** troceado;
    int word_counter;
    bool status=true;


    char echo[MAX_COMM],*cwd= malloc(MAX_COMM* sizeof(char));

        do {
            obt_com(echo[0]);
            exact_comm(echo[0],comm[0]);
            if(strcmp(comm,"pid")) pid(echo);
            if(strcmp(comm,"autores")) autores(echo);
            if(strcmp(comm,"fecha")) fecha();
            if(strcmp(comm,"infosis")) infosis();

            if (!strcmp(comm, "fin") || !strcmp(comm, "salir") || !strcmp(comm, "bye")) status=false;
            /*
            getpwd(cwd);
            printf("\n%s>> ", cwd);
            fgets(echo, 59, stdin);
            troceado = malloc(100 * sizeof(char *));
            word_counter = TrocearCadena(echo, troceado);

             */
        }while(status);


 /*       switch (echo) {
            case "exit":
                return 0;
            break;
            case "autores":
                autores(al[0]);

        }
*/
    }