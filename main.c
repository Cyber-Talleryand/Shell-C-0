#include "func.h"

/*
 * problemas graves
 * -no imprime el numero de link (l 354);
 *
 * */

int main(){
    char aux[MAXTAML];
    tList hist, comando;
    createEmptyList(&hist);
    createEmptyList(&comando);
    bool status=true;

    do {
        obt_com(&comando);
        inPrintList(comando,aux);
        insertItem(aux,&hist);
        status=an_comm(comando, &hist,true);
        deleteList(&comando);
        createEmptyList(&comando);
        printf("\n");
        deleteList(&comando);
        limpiar_string(aux,MAXTAML);
    }while(status);
    deleteList(&hist);
}

void str_to_cmm(char *str, tList* comm) {
    char c, an_str[MAXTAML];
    int aux = 0;
    tPosL p;
    for(int i = 0; str[i]!='\0'; i++){
        c = str[i];
        if(c == ' '){
        	an_str[aux] = '\0';
            insertItem(an_str, comm);
            limpiar_string(an_str,i);
            aux = 0;
        }else if ((c>=65 && c<=90) || (c>=97 && c<=122) || c==45){
            an_str[aux] = c;
            aux++;
        }
    }
    insertItem(an_str, comm);
    insertItem(FIN_COMM,comm);
}

void obt_com(tList* comm) {
    char c, an_str[MAXTAML];
    bool status_comm=true;
    int i = 0;

    limpiar_string(an_str,MAXTAML);
    printf("\n>>");

    do {
        c = getchar();
        if (i >= MAX_COMM || c == EOF || c == '\n') {
            status_comm = false;
            an_str[i] = '\0';
            insertItem(an_str, comm);
        } else if(c == ' '){
        	an_str[i] = '\0';
            insertItem(an_str, comm);
            limpiar_string(an_str,i);
            i = 0;
        }else{
            an_str[i] = c;
            i++;
        }
    } while (status_comm);
    insertItem(FIN_COMM, comm);
}

bool an_comm(tList L, tList *historia, bool check){
    int a=1;
    tList temp;
    createEmptyList(&temp);
    if(strcmp(L->data,"pid")==0) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=pid(L->next->data);
    }
    if(strcmp(L->data,"autores")==0) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=autores(L->next->data);

    }
    if(strcmp(L->data,"fecha")==0){
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=fecha(L->next->data);
    }
    if(strcmp(L->data,"infosis")==0) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=infosis();
    }
    if(strcmp(L->data,"hist")==0) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a= historial(L->next->data,historia);
    }
    if(strcmp(L->data,"ayuda")==0) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else
        a=ayuda(L->next->data);
    }
    if(strcmp(L->data,"carpeta")==0) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=carpeta(L->next->data);
    }
    if(strcmp(L->data,"crear")==0) a= crear(&L->next);
    if(strcmp(L->data,"listfich")==0) a= list_fich(L->next,&temp);
    if(strcmp(L->data,"listdir")==0) a= list_dir_up(L->next, &temp);
    if(strcmp(L->data,"borrar")==0) a= borrar(L->next);
    if(strcmp(L->data,"borrarrec")==0) a= borrarrec(L->next);

    if(strcmp(L->data,"comando")==0) {
        tPosL p;
        p = comando(L->next->data, *historia);
        //printf("Error");
        if (p == NULL) {
            printf("Número de comando inválido");
            a = 0;
        } else {
            tList aux;
            createEmptyList(&aux);
            //char *pre_comm = NULL;
            //strcpy(pre_comm, p->data);
            str_to_cmm(p->data, &aux);
            if (strcmp(aux->data, "comando") != 0) {
                printf("%s\n", aux->data);
                sleep(1);
                an_comm(aux, historia, false);
                deleteList(&aux);
            } else {
                a = 0;
                printf("Estás intentando utilizar un \"comando\" que puede romper el programa");
            }
        }
    }
    if (strcmp(L->data, "fin")==0 || strcmp(L->data, "salir")==0 || strcmp(L->data, "bye")==0)
        return false;
    if(a==2 && !check) printf("Parámetros introducidos incorrectos");
    if(a==1 && !check) printf("No se ha introducido ningún comando válido");
    return true;

}



int autores(char *str){

    if (strcmp(str, FIN_COMM) == 0 ){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
        printf("r.d.gmantuano@udc.es\t\t\t");
        printf("david.alvarez.celemin@udc.es\n");
    }
    if (strcmp(str, "-l") == 0){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
    }
    if (strcmp(str, "-n") == 0) {
        printf("r.d.gmantuano@udc.es\t");
        printf("david.alvarez.celemin@udc.es\n");
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
    if(strcmp(str,FIN_COMM)==0){
        getpwd();
        return 0;
    }
    else if(chdir(str)==0){
        printf("Movido a %s",str);
    }
    else perror("Directorio no válido");
    printf(" ");
    return 0;
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
    }

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
    for(int i = 0; i < c && string[i]!='\0'; i++){
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

int crear(tList *L){
    tList p;
    bool a;
    if(strcmp((*L)->data,"-f")==0) 
    	a=true;
    for(p=(*L)->next; strcmp(p->data,FIN_COMM)!=0;p=p->next){
        crear_x(p,a);
    }
    return 0;
}

int crear_x(tList L, bool a){
    FILE *fp;
    if (a){
        if((fp=fopen(L->data,"r"))!= NULL) {
            printf("Cannot create that file, already exists");
            fclose(fp);
        }
            //Posible perdida de puntero
        else{
            //fclose(fp);
            if((fp=fopen(L->data,"w"))==NULL){
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

void sym_link (struct stat stats){
    //else if(strcmp(comm,"-link")==0){

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
            printf(" -> %s\t", linkname);
        }
        else
            printf("none\t");
    }

}

void printFileProperties(struct stat stats, tList *temp,char* name, char *carpeta){
    struct tm dt;
    /*if(strcmp(FIN_COMM,comm)==0){
        printf("\nFile size: %ld", stats.st_size);
        return;
    }*/
    if(findItem(FIN_COMM,*temp)==NULL/*|| findItem("-long",temp)==NULL && findItem("-link",temp)!=NULL*/){
        if(findItem("-acc",*temp)!=NULL){
            // File modification time
            dt = *(gmtime(&stats.st_mtime));
            printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                   dt.tm_hour, dt.tm_min, dt.tm_sec);
        } else{
            dt = *(gmtime(&stats.st_ctime));
            printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                   dt.tm_hour, dt.tm_min, dt.tm_sec);

        }
        // Get file creation time in seconds and
        // convert seconds to date and time format
        if(findItem("-long",*temp)){

            printf("%lu\t%ld\t",stats.st_nlink,stats.st_ino);

            if (stats.st_mode &  S_IRUSR)
                printf("r ");
            if (stats.st_mode & S_IWUSR)
                printf("w ");
            if (stats.st_mode & S_IXUSR)
                printf("x");
            printf("\t");

        }
        if(findItem("-link",*temp)!=NULL) sym_link(stats);

    }


    // File size
    printf("%ld\t", stats.st_size);
    printf("%s\t",name);
    printf("\n");
}

void get_parameters(tList *L, tList M){
    tPosL p;
    for(p=M;p!=NULL && p->data[0]=='-';p=p->next){
        insertItem(p->data,L);
    }
}

void an_list(tList* L,tList *temp,void (*function)(struct stat stats, tList *temp, char* name, char *carpeta)) {
    tList p;
    struct stat structstat;
    get_parameters(temp, *L);
    if (isEmptyList(*temp)) p = *L;
    else p = findItem(last(*temp)->data, *L)->next;
    for (; p != NULL && strcmp(p->data, FIN_COMM) != 0; p = p->next) {
        if (stat(p->data, &structstat) == 0) {
            (*function)(structstat, temp, p->data, p->data);
        }
    }
    deleteList(temp);
}


int list_fich(tList L, tList *temp){
    if(strcmp(L->data,FIN_COMM)==0) {
        getpwd();
        return 0;
    }
    createEmptyList(temp);
    an_list(&L,temp,&printFileProperties);
    deleteList(temp);
    return 0;
}

int list_dir_up(tList L, tList *temp){
    if(strcmp(L->data,FIN_COMM)==0)
        carpeta(FIN_COMM);
    else{
        createEmptyList(temp);
        an_list(&L, temp, &list_dir_bottom);
        deleteList(temp);
    }
    return 0;
}

void list_dir_bottom(struct stat structstat, tList *temp,char* name, char* carpeta){
    struct dirent *de;
    DIR *dr = NULL;
    bool a=(S_ISDIR(structstat.st_mode)), b=(strcmp(name,".")!=0 && strcmp(name,"..")!=0);
    struct stat sub_structstat;

    //cambia el directorio actual para poder acceder a los archivos
    /*if(strcmp(getcwd(name,MAXTAML),carpeta)!=0){
        if(chdir(carpeta)!=0) {
            strcat(carpeta,"/");
            return;
        }
    }*/
    //Si no es un directorio, imprime la información del archivo
    if(!a&&b) printFileProperties(structstat,temp, name, name) ;
        //si es un directorio lo abre y recorre
    else if (a&&b){
        if ((dr = opendir(name)) == NULL) {
            perror(name);
            return;
        }
        while ((de=readdir(dr))!=NULL){

            if((a=(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0)) && (b=stat(de->d_name,&sub_structstat)==0)){
                //problema aquí
                if(S_ISDIR(sub_structstat.st_mode))
                    list_dir_bottom(sub_structstat,temp,de->d_name, carpeta/*strcat(carpeta,de->d_name)*/);
                //else printFileProperties(sub_structstat,temp,)
            }
            else if(!a);
            else  perror(de->d_name);

        }
        closedir(dr);

    }




}

void leeCarpeta(char *str){
    DIR *dirp;
    struct dirent *e;
    errno = 0;
    if ((dirp = opendir(str)) == NULL) {
        perror(str);
        return;
    }
    while((e = readdir(dirp)) != NULL){
        if((strcmp(e->d_name, ".") * strcmp(e->d_name, "..")) != 0){
            //función
        }
    }
}



int borrar(tList L){
    if(strcmp(L->data,FIN_COMM)==0){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; strcmp(p->data, FIN_COMM)!=0; p = p->next){
            if(remove(p->data) != 0){
                perror(p->data);
                printf("\n");
            }
        }
        return 0;
    }
}
void rec(char *str){
	char source[MAX_COMM];
	getcwd(source, MAX_COMM);
    struct stat structstat;
    if(stat(str, &structstat) != 0)
        perror(str);
    /*if(LetraTF(structstat.st_mode) != 'd'){
        if(remove(str) != 0)
            perror(str);
        return;
    }*/
    DIR *dirp;
    struct dirent *e;
    errno = 0;
    if ((dirp = opendir(str)) == NULL)
        perror(str);
    else{
    	chdir(str);
		while((e = readdir(dirp)) != NULL){
		    if((strcmp(e->d_name, ".") * strcmp(e->d_name, "..")) != 0){
		        if(remove(e->d_name) != 0)
					rec(e->d_name);
				else
					perror(e->d_name);
		    }
		}
		chdir(source);
		if(remove(str) != 0)
			perror(str);
	}
}

int borrarrec(tList L){
    if(strcmp(L->data,FIN_COMM)==0){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; strcmp(p->data, FIN_COMM)!=0; p = p->next){
            if(remove(p->data) != 0){
                if(errno == 39)
                    rec(p->data);
                else
                    perror(p->data);
            }
        }
    }
    return 0;
}
