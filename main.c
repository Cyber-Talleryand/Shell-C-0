
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include "dynamic_list.h"
#include <stdlib.h>
#include "func.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>



int main(){
    char aux[MAXTAML], comm[MAX_COMM];
    tList hist,comando;
    createEmptyList(&hist);
    createEmptyList(&comando);
    bool status=true;

	do {
		obt_com(&comando);
        inPrintList(comando,&aux);
	    insertItem(aux,&hist);
	    status=an_comm(comando, &hist);
        deleteList(&comando);
        createEmptyList(&comando);
	    printf("\n");
        deleteList(&comando);
        limpiar_string(&aux,MAXTAML);
	}while(status);
    deleteList(&hist);
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

bool an_comm(tList L, tList *historia){
    char aux[MAXTAML], aux_infosis[14]="infosis";
    strcpy(aux, L->data);
    int a=1;

    //strcpy(aux, L->data);
    if(strcmp(L->data,"pid")==0) a=pid(L->next->data);
    if(strcmp(L->data,"autores")==0) a=autores(L->next->data);
    if(strcmp(L->data,"fecha")==0) a=fecha(L->next->data);
    if(strcmp(L->data,"infosis")==0) a=infosis();
    if(strcmp(L->data,"hist")==0) a=historial(L->next->data,historia);
    if(strcmp(L->data,"ayuda")==0) a=ayuda(L->next->data);
    if(strcmp(L->data,"carpeta")==0) a=carpeta(L->next->data);
    if(strcmp(L->data,"crear")==0) a= crear_x(L->next);
    if(strcmp(L->data,"listfich")==0) a= list_fich(L);

    if(strcmp(L->data,"comando")==0){

        tPosL p;
        p=comando(L->next->data, *historia);
        if(p==NULL){
            printf("Número de comando inválido");
            a=0;
        }
        else if(strcmp(L->next->data,"comando") != 0) an_comm(p, historia);
        else{
            a=0;
            printf("Estás intentando reutilizar un \"comando\" lo cual puede romper el programa");
        }
    }
    if (strcmp(aux, "fin")==0 || strcmp(aux, "salir")==0 || strcmp(aux, "bye")==0)
        return false;
    if(a!=0) printf("No se ha introducido ningún comando válido");
    return true;

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
        deleteList(L);
    else if(strcmp(str, "0")>=0 && atoi(str)<=999){
        i=strtol(str, NULL, 10);
        print_list(*L, i);
    }
    return 0;
}
int carpeta (char str[]){
    if(chdir(str)!=0){
        if(strcmp(str,FIN_COMM)==0)getpwd();
        else printf("Directorio no válido\n");
        return 0;
    }
    else{
        printf("Movido a %s",str);
        return 0;
    }
}
int getpwd(){
    char aux[60];
    getcwd(aux, MAX_COMM);
    printf("%s\n",aux);
    return 0;
}
tPosL comando(char *str, tList L) {
    tPosL p;
    int a, i = 0;
    a = atoi(str);
    a--;
    for (p = L; p != NULL && i < a; p = p->next) {
        i++;
    };

    if (a <= i) {
        printf("(*) %s\n", p->data);
        return p;
    }
    else return NULL;
}


int ayuda(char *str){
    if(strcmp(str,"pid")==0) ayuda_pid();
    if(strcmp(str,"autores")==0) ayuda_autores();
    if(strcmp(str,"fecha")==0) ayuda_fecha();
    if(strcmp(str,"infosis")==0) ayuda_infosis();
    if(strcmp(str,"hist")==0) ayuda_historial();
    if(strcmp(str,"ayuda")==0) ayuda_ayuda();
    if(strcmp(str,"carpeta")==0) ayuda_carpeta();
    if(strcmp(str,"comando")==0) ayuda_comando();
    if (strcmp(str, "fin")==0 || strcmp(str, "salir")==0 || strcmp(str, "bye")==0) ayuda_salir();
    return 0;
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



void limpiar_string(char* string, int c){
    for(int i = 0; i < c && string[i]!='/0'; i++){
        string[i] = '\0';
    }

}


char LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char * ConvierteModo (mode_t m, char *permisos)
{
    strcpy (permisos,"---------- ");
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r'; /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r'; /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r'; /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s'; /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';
    return permisos;
}

int crear_x(tList L){
    FILE *fp;
    if (strcmp(L->data,"-f")==0){
        if((fp=fopen(L->next->data,"r"))!=NULL) {
            printf("Cannot create that file, already exists");
            fclose(fp);
        }
            //Posible perdida de puntero
        else{
            //fclose(fp);
            if((fp=fopen(L->next->data,"w"))==NULL){
                printf("Cannot create that file");
            }
            else fclose(fp);
        }
    }
    else{
        if (mkdir(L->data, 0777) == -1){
            printf("Error al crear el directiorio");
        }
        else
            printf("Directory created %s",L->data);
    }
    return 0;
}


void printFileProperties(struct stat stats, char comm[]){
    struct tm dt;
    if(strcmp(FIN_COMM,comm)==0){
        printf("\nFile size: %ld", stats.st_size);
        return;
    }

    if(strcmp(comm,"-acc")==0){
        // File modification time
        dt = *(gmtime(&stats.st_mtime));
        printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
               dt.tm_hour, dt.tm_min, dt.tm_sec);
    }
    // Get file creation time in seconds and
    // convert seconds to date and time format
    if(strcmp(comm,"-long")==0){
        dt = *(gmtime(&stats.st_ctime));
        printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
               dt.tm_hour, dt.tm_min, dt.tm_sec);
    }















        else if(strcmp(comm,"-link")==0){

//      Solucion copiada
//        long symlink_max;
//        size_t bufsize;
//        char *buf;
//        ssize_t len;
//
//        errno = 0;
//        symlink_max = pathconf("/usr/bin/", _PC_SYMLINK_MAX);
//        if (symlink_max == -1) {
//            if (errno != 0) {
//                /* handle error condition */
//            }
//            bufsize = 10000;
//        }
//        else {
//            bufsize = symlink_max+1;
//        }
//
//        buf = (char *)malloc(bufsize);
//        if (buf == NULL) {
//            /* handle error condition */
//        }
//
//        len = readlink("/usr/bin/perl", buf, bufsize);
//        buf[len] = '\0';*/
            char linkname[MAX_MID];
            char cwd[MAX_MID];


            if(getcwd(cwd,sizeof(cwd))!=NULL){
                ssize_t r = readlink(cwd, linkname, MAX_MID);

                if (r != -1) {
                    linkname[r] = '\0';
                    printf(" -> %s\n", linkname);
                }
                else
                    putchar('\n');
            }

        }





        printf("\nFile access: ");
        if (stats.st_mode & R_OK)
            printf("read ");
        if (stats.st_mode & W_OK)
            printf("write ");
        if (stats.st_mode & X_OK)
            printf("execute");

        // File size
        printf("\nFile size: %ld", stats.st_size);

    }


int list_fich(tList L){
    tPosL p;
    char aux[MAX_AUX_COMM]=FIN_COMM;
    struct stat structstat;
    //check optional parameters for the function
    if(strcmp(L->data,FIN_COMM)==0) {
        carpeta(L->data);
        return 0;
    }

    if(L->data[0]=='-')strcpy(aux,L->data);

    if(L->next->data[0]=='-') return 0;



    for ( p=L;  p!=NULL && strcmp(p->data,FIN_COMM)!=0 ; p=p->next ) {
        if( access( p->data, F_OK ) == 0 ) {
            if(stat(p->data, &structstat)){
                printf("%s",p->data);
                printFileProperties(structstat,aux);
            }
        } else {
            // file doesn't exist
            // Q_P What we do if wrong option?
        }
        printf("\n");
    }

}