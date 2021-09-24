/*Cosas que quedan por hacer
 *
 * ayuda[cmd}
 * pasar argumentos
 * Carpeta
 * Comprobar que se cumples las condiciones iniciales del bucle (son 5) del paper
 * */
/*
 * Problemas que quedas por solucionar de esta implementacion
 * -Exact_arg
 *
 * Apreciaciones sobre cosas que vas a tener que cambiar
 * Tu propusiste dos comandos para dynamic_list.c
 * Savelist y transferlist. Quiero decir que modifiques esos archivos si ves que necesitas algo adicional
 * Psdt: Me acabo de acordar que necesitas un comando para printear la  lista y ten en cuenta que la printeamos
 * con una cabecera que no se guarda en el comando (documentación)
 *
 * Comandos a modificar por tu parte principalmente
 * obt_comm
 * search_comm
 * exact_comm
 * exact_arg(este no funciona)
 * */


#include <stdio.h>

#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include "dynamic_list.h"
#include <stdlib.h>

#define MAX_COMM 999
#define MAX_AUX_COMM 20
#define ERR_INT -1
#define ERR_CHAR '$'
#define FIN_COMM "-0"

//Vamos a definir una estructura variable para almacenar un numero ilimitado de comandos


void limpiar_string(char* string, int c){
	for(int i = 0; i < c && string[i]!='/0'; i++){
		string[i] = '\0';
	}

}

void obt_com(tList* comm) {
    char c, an_str[MAXTAML];
    bool status_comm=true;
    int i = 0;

    limpiar_string(&an_str,MAXTAML);
    printf("\n>>");

    do {
        c = getchar();
        if (i >= MAX_COMM || c == EOF || c == '\n') {
            status_comm = false;
            insertItem(an_str, comm);
            an_str[i] = '\0';
        } else if(c == ' '){
        	insertItem(an_str, comm);
        	limpiar_string(&an_str,i);
        	i = 0;
        }else{
            an_str[i] = c;
            i++;
        }
    } while (status_comm);
    insertItem(FIN_COMM, comm);
}

/*
int search_arg(char *an_str){
    int i=0;
    for(i=0;i<MAX_COMM && an_str[i]!=' ' && an_str[i]!='\0';i++);
    if(i==0) return 0;
    else if(i<MAX_COMM && i>0 && an_str[i+1]==' ')return i;
    else return ERR_INT;
}*/
/*
//Usar wordcounter para implementar esta función correctamente
int search_next_arg(char *an_str, int f){
    int i;
    for(i=f;i<MAX_COMM && an_str[i]!=' ';i++);
    if(i<MAX_COMM)return i;
    else return ERR_INT;
}
void exact_comm(char *an_str,char *dev){
    int i,cont;
    for(i=0;i<MAX_COMM  && an_str[i]!='\0'&& an_str[i]!='\n';i++);
    for(cont=0;cont<=i;cont++){
        dev[cont]=an_str[cont];
    }
    dev[cont+1]='\n';
}
*/
/*
void exact_comm(char an_str[],char *dev){
    int i,cont;
    for(i=0;i<MAX_COMM  && an_str[i]!='\0'&& an_str[i]!='\n' && an_str[i]!=' ';i++);
    for(cont=0;cont<=i;cont++){
        dev[cont]=an_str[cont];
    }
    dev[cont+1]='\n';
}
*/
/*char exact_arg(char *an_str,int i){
    if(i==ERR_INT) return ERR_CHAR;
    if(an_str[i]==' ') i++;
    if(an_str[i]=='-') i++;
    return an_str[i];
}*/

int getpwd(){
        char aux[60];
        getcwd(aux, MAX_COMM);
        printf("%s\n",aux);
    return 0;
}



int autores(char *str){

    if (strcmp(str, FIN_COMM) == 0 ){
        printf("Rodrigo Dantes Gonzalez Mantuano");
        printf("David Álvarez Celemín");
        printf("r.d.gmantuano@udc.es");
        printf("david.alvarez.celemin@udc.es");
    }
    if (strcmp(str, "-l") == 0){
        printf("Rodrigo Dantes Gonzalez Mantuano");
        printf("David Álvarez Celemín");
    }
    if (strcmp(str, "-n") == 0) {
        printf("r.d.gmantuano@udc.es");
        printf("david.alvarez.celemin@udc.es");
    }
    return 0;
}

int fecha(char *str){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if(strcmp(str,"-d")==0)printf("%d-%02d-%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    else if(strcmp(str,"-l")==0)printf("%02d:%02d:%02d",tm.tm_hour, tm.tm_min, tm.tm_sec);
    else if(strcmp(str,FIN_COMM)==0)printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
    return 0;
}

int infosis(){
    struct utsname aux;
    uname(&aux);
    printf("%s",aux.sysname);
    return 0;
}

int pid(char *str){
    pid_t process_id;
    if(strcmp(str, "-p") == 0)
        printf("Parent_PID Terminal: %d\n",getppid());
    else if(strcmp(str, FIN_COMM) == 0)
        printf("PID Terminal: %d\n",getpid());
    else
        printf("Incorrect argument (check the documentation)");
    return 0;

}
int historial(char *str,tList *L){
    int i;
    if(strcmp(str, FIN_COMM) == 0)
        print_list(*L, MAX_COMM);
    else if(strcmp(str, "-c") == 0)
        deleteList(L,false);
    else if(strcmp(str, "0")>=0 && atoi(str)<=999){
        i=strtol(str, NULL, 10);
        print_list(*L, i);
    }
    return 0;
}

int carpeta (char *PATH){
    if(chdir(*PATH)!=0) printf("Directorio no válido");
}

void ayuda_comando(){
    printf("Reutiliza el comando del historial correspodiente al número intrducido");
}
void ayuda_pid(){
    printf("Muestra el PID del programa\n En caso de pasar el parámetro -p se muestra el del proceso padre");
}
void ayuda_autores(){
    printf("Muestra los datos de los autores\n\"-l\"para solo ver los correos\n\"-n\" para solo los nombres de los creadores");
}
void ayuda_fecha(){
    printf("Muestra la fecha y la hora del sistema por defecto\n\"-d\" para solo ver la fecha");
}
void ayuda_infosis(){
    printf("Muestra la información del sistema operativo\n");
}
void ayuda_getpwd(){
    printf("Muestra el directorio actual de ejecución de la shell");
}
void ayuda_historial(){
    printf("Muestra los comandos utilizados anteriormente\n\"-N\" Muestra solo los N primero elementos \n\"-c\"Resetea la tabla");
}
void ayuda_ayuda(){
    printf("Muestra la documentación de los comandos");
}
void ayuda_carpeta(){
    printf("Redirige el shell del directorio actual al directorio destino");
}
void ayuda_salir(){
    printf("Saca al usuario de la shell");
}

int ayuda(char *str){
    /*int i; char aux;
    i=search_arg(str);aux=exact_arg(str,i);
    if(strcmp(aux,"pid")==0) ayuda_pid();
    if(strcmp(aux,"autores")==0) ayuda_autores;
    if(strcmp(aux,"fecha")==0) ayuda_fecha();
    if(strcmp(aux,"infosis")==0) ayuda_infosis();
    if(strcmp(aux,"getpwd")==0) ayuda_getpwd();
    if(strcmp(aux,"hist")==0) ayuda_historial;
    if(strcmp(aux,"ayuda")==0) ayuda_ayuda();
    if(strcmp(aux,"carpeta")==0) ayuda_carpeta();
    if (strcmp(aux, "fin")==0 || strcmp(aux, "salir")==0 || strcmp(aux, "bye")==0) ayuda_salir;*/
    if(strcmp(str,"pid")==0) ayuda_pid();
    if(strcmp(str,"autores")==0) ayuda_autores;
    if(strcmp(str,"fecha")==0) ayuda_fecha();
    if(strcmp(str,"infosis")==0) ayuda_infosis();
    if(strcmp(str,"getpwd")==0) ayuda_getpwd();
    if(strcmp(str,"hist")==0) ayuda_historial;
    if(strcmp(str,"ayuda")==0) ayuda_ayuda();
    if(strcmp(str,"carpeta")==0) ayuda_carpeta();
    if (strcmp(str, "fin")==0 || strcmp(str, "salir")==0 || strcmp(str, "bye")==0) ayuda_salir;
    return 0;
}


tPosL comando(char *str, tList L){
    tPosL p;
    p=findItem(str, L);
    printf("(*) %s",p->data);
    return p;
}

bool an_comm(tList L, tList *historia){
    char aux[MAXTAML], aux_infosis[14]="infosis";
    strcpy(aux, L->data);
    int a;

//    tList X=*L;
    //exact_comm(echo,aux[0]);
    strcpy(aux, L->data);
   // pid(L->next->data);
    if(strcmp(aux,"pid")==0) a=pid(L->next->data);
    if(strcmp(aux,"autores")==0) a=autores(L->next->data);
    if(strcmp(aux,"fecha")==0) a=fecha(L->next->data);
    if(strcmp(aux,aux_infosis)==0) a=infosis();
    if(strcmp(aux,"getpwd")==0) a=getpwd();
    if(strcmp(aux,"hist")==0) a=historial(L->next->data,historia);
    if(strcmp(aux,"ayuda")==0) a=ayuda(L->next->data);
    if(strcmp(aux,"carpeta")==0) a=carpeta(L->next->data);
 /*   if(strcmp(aux,"comando")==0){
        char aux2;
        p=comando(L->next->data, *historia);
        exact_comm(p->data,&aux2);
        if(strcmp(L->next->data,"comando") != 0)
            return an_comm(L->next, L);
        else{
            printf("Estás intentando reutilizar un \"comando\" lo cual puede romper el programa");
        }
    }*/
    if (strcmp(aux, "fin")==0 || strcmp(aux, "salir")==0 || strcmp(aux, "bye")==0)
        return false;
//    insertItem(inPrintList(L), historial);
    if(a!=0) printf("No se ha introducido ningún comando válido");
    return true;

}

//Todo finalizado hasta aquí



//Devuelve el tamaño de la string en palabras
int TrocearCadena(char * cadena, char ** trozos){
    int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL) return 0;
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) i++;
    return i;
}



int main(){
    char aux[MAXTAML], comm[MAX_COMM];
    tList hist,comando;
    createEmptyList(&hist);
    createEmptyList(&comando);

    char** troceado;
    int word_counter;
    bool status=true;


    char echo[MAX_COMM], *cwd= malloc(MAX_COMM* sizeof(char));
	do {
		obt_com(&comando);
//	    strcpy(echo,"pid -p");
        inPrintList(comando,&aux);
	    insertItem(aux,&hist);
	    status=an_comm(comando, &hist);
//        multitouni(&comando);
//        insertItem(comando->data,&hist);
        deleteList(&comando, false);
	    /*Al pasar el comando anterior se cambia el valor de lastItem->next de (0x00) a (0xa00) produciendo errores*/
	    printf("\n");
        deleteList(&comando,true);
	}while(status);
    deleteList(&hist, true);
}

//La funcion devuelve el directorio actual de ejecucion del terminal
    /*
            getpwd(cwd);
            printf("\n%s>> ", cwd);
            fgets(echo, 59, stdin);
            troceado = malloc(100 * sizeof(char *));
            word_counter = TrocearCadena(echo, troceado);
             */

/*       switch (echo) {
           case "exit":
               return 0;
           break;
           case "autores":
               autores(al[0]);
       }
*/
