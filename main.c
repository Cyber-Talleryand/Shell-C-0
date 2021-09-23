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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include "dynamic_list.h"


#define MAX_COMM 600
#define MAX_AUX_COMM 20
#define ERR_INT -1
#define ERR_CHAR '$'

//Vamos a definir una estructura variable para almacenar un numero ilimitado de comandos


void obt_com(char *an_str) {
    char c;
    bool status_comm=true;
    int i = 0;
    printf("\n>>");
    do {
        c = getchar();
        if (i >= MAX_COMM || c == EOF || c == '\n') {
            status_comm = false;
            an_str[i] = '\0';
        } else {
            an_str[i] = c;
            i++;
        }
    } while (status_comm);

}


int search_arg(char *an_str){
    int i=0;
    for(i=0;i<MAX_COMM && an_str[i]!=' ' && an_str[i]!='\0';i++);
    if(i==0) return 0;
    else if(i<MAX_COMM && i>0 && an_str[i+1]==' ')return i;
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

void exact_comm(char *an_str,char *dev){
    int i,cont;
    for(i=0;i<MAX_COMM  && an_str[i]!='\0'&& an_str[i]!='\n';i++);
    for(cont=0;cont<=i;cont++){
        dev[cont]=an_str[cont];
    }
    dev[cont+1]='\n';

}
*/
void exact_comm(char an_str[],char *dev){
    int i,cont;
    for(i=0;i<MAX_COMM  && an_str[i]!='\0'&& an_str[i]!='\n' && an_str[i]!=' ';i++);
    for(cont=0;cont<=i;cont++){
        dev[cont]=an_str[cont];
    }
    dev[cont+1]='\n';

}
char exact_arg(char *an_str,int i){
    if(i==ERR_INT) return ERR_CHAR;
    if(an_str[i]==' ') i++;
    if(an_str[i]=='-') i++;
    return an_str[i];
}

void getpwd(){
        char aux[60];
        getcwd(aux, MAX_COMM);
        printf("%s\n",aux);
}



void autores(char *str){
    int i; char aux;
    i=search_arg(str);aux= exact_arg(str,i);
    if (aux!='l'){
        printf("Rodrigo Dantes Gonzalez Mantuano");
        printf("David Álvarez Celemín");
    }
    if (aux!='n'){
        printf("r.d.gmantuano@udc.es");
        printf("david.alvarez.celemin@udc.es");
    }
}

int fecha(char *str){
    int i; char aux;
    i=search_arg(str);aux=exact_arg(str,i);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if(aux=='d')printf("%d-%02d-%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    if(aux=='l')printf("%02d:%02d:%02d",tm.tm_hour, tm.tm_min, tm.tm_sec);
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
    else if (aux==ERR_CHAR)  printf("PID Terminal: %d\n",getpid());
    else printf("Argument incorrect (check the documentation)");


    return 0;

}
void historial(char *str,tList *L){
    int i; char aux;
    i=search_arg(str);aux=exact_arg(str,i);
    if(aux==ERR_CHAR) print_list(*L,MAX_COMM);
    if(aux=='c') deleteList(L,false);
    if(aux>='0' && aux<MAX_COMM){
        i=atoi(&aux);
        print_list(*L,i);
    }
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
    printf("Muestra la fecha y la hora del sistema por defecto\n\"-d\" para solo ver la fecha\n\"-d\"");
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

void ayuda(char *str){
    int i; char aux;
    i=search_arg(str);aux=exact_arg(str,i);
    if(strcmp(aux,"pid")==0) ayuda_pid();
    if(strcmp(aux,"autores")==0) ayuda_autores;
    if(strcmp(aux,"fecha")==0) ayuda_fecha();
    if(strcmp(aux,"infosis")==0) ayuda_infosis();
    if(strcmp(aux,"getpwd")==0) ayuda_getpwd();
    if(strcmp(aux,"hist")==0) ayuda_historial;
    if(strcmp(aux,"ayuda")==0) ayuda_ayuda();
    if(strcmp(aux,"carpeta")==0) ayuda_carpeta();
    if (strcmp(aux, "fin")==0 || strcmp(aux, "salir")==0 || strcmp(aux, "bye")==0) ayuda_salir;
}


tPosL comando(char *str, tList *L){
    tPosL p;
    p=findItem(str,*L);
    printf("(*) %s",p->data);
    return p;
}

bool an_comm(char *echo,tList *L){
    char *aux[MAX_AUX_COMM];
    tPosL p;

//    tList X=*L;
    exact_comm(echo,aux[0]);
    if(strcmp(aux,"pid")==0) pid(echo);
    if(strcmp(aux,"autores")==0) autores(echo);
    if(strcmp(aux,"fecha")==0) fecha(echo);
    if(strcmp(aux,"infosis")==0) infosis();
    if(strcmp(aux,"getpwd")==0) getpwd();
    if(strcmp(aux,"hist")==0) historial(echo,L);
    if(strcmp(aux,"ayuda")==0) ayuda(echo);
    if(strcmp(aux,"comando")==0){
        char aux2;
        p=comando(echo,L);
        exact_comm(p->data,&aux2);
        if(strcmp(aux2,"comando")!=0)an_comm(p->data,L);
        else{
            printf("Estás intentando reutilizar un \"comando\" lo cual puede romper el programa");
        }
    }
    if (strcmp(aux, "fin")==0 || strcmp(aux, "salir")==0 || strcmp(aux, "bye")==0) return false;
    return true;

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
    tList hist,reserva;
    createEmptyList(&hist);


    char** troceado;
    int word_counter;
    bool status=true;


    char echo[MAX_COMM],*cwd= malloc(MAX_COMM* sizeof(char));
        do {
 //           obt_com(&echo[0]);
            strcpy(echo,"pid -p");
            insertItem(echo,&hist);
            status=an_comm(echo,&hist);
            /*Al pasar el comando anterior se cambia el valor de lastItem->next de (0x00) a (0xa00) produciendo errores*/
            printf("\n");
        }while(status);
    deleteList(&hist,true);


    }


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