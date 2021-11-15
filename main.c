#include "func.h"
/*@Alvaro revisa si el cambio char *str => char *str[] es correcto*/
int main(){
    char aux[MAXTAML];
    tList hist, comando, dynamic_memory;
    createEmptyList(&hist);
    createEmptyList(&dynamic_memory);
    bool status=true;

    do {
        createEmptyList(&comando);
        obt_com(&comando);
        inPrintList(comando,aux);
        insertItem(aux,&hist);
        status=an_comm(comando, &hist, &dynamic_memory,true);
        deleteList(&comando);
        printf("\n");
        limpiar_string(aux,MAXTAML);
    }while(status);
    deleteList(&hist);
}


bool an_comm(tList L, tList *historia, tList *dynamic_memory,bool check){
    int a=1;
    tList temp;
    createEmptyList(&temp);
    if(is_comm_equals(L->data,"pid")) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=pid(L->next->data);
    }
    if(is_comm_equals(L->data,"autores")) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=autores(L->next->data);

    }
    if(is_comm_equals(L->data,"fecha")){
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=fecha(L->next->data);
    }
    if(is_comm_equals(L->data,"infosis")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=infosis();
    }
    if(is_comm_equals(L->data,"hist")) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a= historial(L->next->data,historia);
    }
    if(is_comm_equals(L->data,"ayuda")) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else
            a=ayuda(L->next->data);
    }
    if(is_comm_equals(L->data,"carpeta")) {
        if(count_node(L->next)>2){
            check=false;
            a=2;
        }
        else a=carpeta(L->next->data);
    }
    if(is_comm_equals(L->data,"crear")) a= crear(L->next);
    if(is_comm_equals(L->data,"listfich")) a= list_fich(L->next,&temp);
    if(is_comm_equals(L->data,"listdir")) a= list_dir_up(L->next, &temp);
    if(is_comm_equals(L->data,"borrar")) a= borrar(L->next);
    if(is_comm_equals(L->data,"borrarrec")) a= borrarrec(L->next);

    if(is_comm_equals(L->data,"comando")) {
        tPosL p;
        p = comando(L->next->data, *historia);
        if (p == NULL) {
            printf("Número de comando inválido");
            a = 0;
        } else {
            tList aux;
            createEmptyList(&aux);
            str_to_cmm(p->data, &aux);
            if (!is_comm_equals(aux->data, "comando")) {
                printf("%s\n", aux->data);
                sleep(1);
                an_comm(aux, historia, dynamic_memory,  false);
            } else {
                a = 0;
                printf("Estás intentando utilizar un \"comando\" que puede romper el programa");
            }
            deleteList(&aux);
        }
    }
    deleteList(&temp);
    if (is_comm_equals(L->data, "fin") || is_comm_equals(L->data, "salir") || is_comm_equals(L->data, "bye"))
        return false;
    if(a==2 && !check) printf("Parámetros introducidos incorrectos");
    if(a==1 && !check) printf("No se ha introducido ningún comando válido");
    return true;

}


int autores(char *str){

    if (is_comm_void(str) ){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
        printf("r.d.gmantuano@udc.es\t\t\t");
        printf("david.alvarez.celemin@udc.es\n");
    }
    if (is_comm_equals(str, "-l")){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
    }
    if (is_comm_equals(str, "-n")) {
        printf("r.d.gmantuano@udc.es\t");
        printf("david.alvarez.celemin@udc.es\n");
    }
    return 0;
}
int fecha(char *str){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if(is_comm_equals(str,"-d"))printf("%d-%02d-%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    else if(is_comm_equals(str,"-l"))printf("%02d:%02d:%02d",tm.tm_hour, tm.tm_min, tm.tm_sec);
    else if(is_comm_void(str))printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
    return 0;
}
int infosis(){
    struct utsname aux;
    uname(&aux);
    printf("%s",aux.sysname);
    return 0;
}
int pid(char *str){
    if(is_comm_equals(str, "-p"))
        printf("Parent_PID Terminal: %d\n",getppid());
    else if(is_comm_void(str))
        printf("PID Terminal: %d\n",getpid());
    else
        printf("Incorrect argument (check the documentation)");
    return 0;

}
int historial(char *str,tList *L){
    int i;
    if(is_comm_void(str))
        print_list(*L, MAX_COMM);
    else if(is_comm_equals(str, "-c"))
        deleteList(L);
    else if(strcmp(str, "0")>=0 && atoi(str)<=999){
        i=strtol(str, NULL, 10);
        print_list(*L, i);
    }
    else return 1;
    return 0;
}
int carpeta (char str[]){
    if(is_comm_void(str)){
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
    if(is_comm_equals(str,"pid")) ayuda_pid();
    if(is_comm_equals(str,"autores")) ayuda_autores();
    if(is_comm_equals(str,"fecha")) ayuda_fecha();
    if(is_comm_equals(str,"infosis")) ayuda_infosis();
    if(is_comm_equals(str,"hist")) ayuda_historial();
    if(is_comm_equals(str,"ayuda")) ayuda_ayuda();
    if(is_comm_equals(str,"carpeta")) ayuda_carpeta();
    if(is_comm_equals(str,"comando")) ayuda_comando();
    if (is_comm_equals(str, "fin") || is_comm_equals(str, "salir") || is_comm_equals(str, "bye")==0) ayuda_salir();
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
void ayuda_crear(){
    printf("Crea directorio en la carpeta actual\n "
           "Si se usa la opción \"-f\" se crea un fichero en lugar de un directorio");
}

void ayuda_listfich(){
    printf("Imprime la información de los archivos que van a continuación del comando\n"
           "\"-long\" amplía la información sobre los archivos"
           "\"-link\" muestra la relación simbólica con otros archivos"
           "\"-acc\" substituye la fecha de última modificación por la de último acceso"
            "Si no hay parámetros imprime la dirección del directorio actual\n"
           "");
}
void ayuda_listdir(){
    printf("");
}
void ayuda_borrar(){
    printf("Borra los archivos o directorios vacíos indicados");
}
void ayuda_borrarrec(){
    printf("Borra los directorios o archivos de forma recursiva");
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

int crear(tList L){
    tList p;
    bool a = false;
	if(is_comm_equals(L->data,"-f")){
		a = true;
		L = L-> next;
	}
	for(p=L; !is_comm_void(p->data);p=p->next)
        crear_x(p, a);
    return 0;
}

int crear_x(tList L, bool cond){
    FILE *fp;
    if (cond){
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
    }else if (mkdir(L->data, 0777) == -1)
            printf("Error al crear el directiorio");
        else
            printf("Directory created %s",L->data);
    return 0;
}

void sym_link (){

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

void printFileProperties(struct stat stats, tList *temp,char* name){
    struct tm dt;
    if(!(name[0] == '.' && findItem("-hid",*temp)==NULL)){
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
		    if(findItem("-link",*temp)!=NULL) sym_link();

		}


		// File size
		printf("%ld\t", stats.st_size);
		printf("%s\t",name);
		printf("\n");
	}
}

void get_parameters(tList *L, tList M){
    tPosL p;
    for(p=M;p!=NULL && p->data[0]=='-';p=p->next){
        insertItem(p->data,L);
    }
}

void an_list(tList* L,tList *temp,void (*function)(struct stat stats, tList *temp, char* name)) {
    tList p;
    struct stat structstat;
    get_parameters(temp, *L);
    if (isEmptyList(*temp)) p = *L;
    else p = findItem(last(*temp)->data, *L)->next;
    for (; p != NULL && !is_comm_void(p->data); p = p->next) {
        if (stat(p->data, &structstat) == 0) {
            (*function)(structstat, temp, p->data);
        }
    }
    deleteList(temp);
}


int list_fich(tList L, tList *temp){
    if(is_comm_void(L->data)) {
        getpwd();
        return 0;
    }
    createEmptyList(temp);
    an_list(&L,temp,&printFileProperties);
    deleteList(temp);
    return 0;
}

int list_dir_up(tList L, tList *temp){
    if(is_comm_void(L->data))
        carpeta(FIN_COMM);
    else{
        createEmptyList(temp);
        an_list(&L, temp, &list_dir_bottom);
        deleteList(temp);
    }
    return 0;
}

void list_dir_bottom(struct stat structstat, tList *temp,char* name){
    struct dirent *de;
    DIR *dr = NULL;
    bool a=(S_ISDIR(structstat.st_mode)), b=(strcmp(name,".")!=0 && strcmp(name,"..")!=0);
    struct stat sub_structstat;
    char source[MAX_COMM];
    getcwd(source, MAX_COMM);
    //Si no es un directorio, imprime la información del archivo
    if(!a)
        printFileProperties(structstat,temp, name) ;
        //si es un directorio lo abre y recorre
    else if (a&&b){
    	printf("\n%s->\n", name);
        if ((dr = opendir(name)) == NULL) {
            perror(name);
            return;
        }
        chdir(name);
        while ((de=readdir(dr))!=NULL){
            stat(de->d_name, &sub_structstat);
            list_dir_bottom(sub_structstat, temp, de->d_name);
        }
        closedir(dr);
        chdir(source);
    }
}

int borrar(tList L){
    if(is_comm_void(L->data)){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; is_comm_void(p->data); p = p->next){
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
    if(is_comm_void(L->data)){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; is_comm_void(p->data); p = p->next){
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

void malloc_general(char *str, char *size, MemList *dynamic_register){
    long i;
    int in;
    char *rubbish,input_list[MAX_AUX_COMM];
    void *a;
    MemPos p,*aux;
    if(is_comm_void(size)){
        for(p=*dynamic_register;p!=NULL;p=p->next){
            printf("%p: size:%ld. malloc %d-%02d-%02d \n",p->memdir,p->size,p->date.tm_year+1900,p->date.tm_mon,p->date.tm_mday);
        }

    }
    if(is_comm_void(str)){
        i= strtol(size,&rubbish,10);
        if(i>0 && rubbish==NULL){
            aux=createItemMemo(i);
            (*aux)->typeId=memo;
            insertItemMemo(aux,dynamic_register);
        }
        else if(strcmp(str,"free")==0){
            i= strtol(size,&rubbish,10);
            p=findSizeMemo(i,*dynamic_register);
            if(p!=NULL){
                deleteAtPositionMemo(p,dynamic_register);
                return;
            }
        }
        else{
            perror("Parámetros introducidos incorrectos");
        }
        return;
    }


}

void dealloc(char *str, char id_memo, MemList* L){
    

   if(is_comm_equals(str,"-malloc")){
       malloc_general("-free",&id_memo,L);
   }
   else if(is_comm_equals(str,"-shared")){

   }
   else if(is_comm_equals(str,"-mmap")){

   }
   else if(is_comm_void(str) && !is_comm_void(&id_memo)){
        MemPos p;
        void* i;
        char* rubbish;
        i= (void *) strtol(&id_memo, &rubbish, 16);
        p= findDirMemo(i,*L);
        if(p!=NULL){
            deleteAtPositionMemo(p,L);
        }
   }
   else if(is_comm_void(str)){
       print_memory_list(L);
   }


    
}


ssize_t LeerFichero (char *fich, void *p, ssize_t n)
{ /* le n bytes del fichero fich en p */
    ssize_t nleidos,tam=n; /*si n==-1 lee el fichero completo*/
    int df, aux;
    struct stat s;
    if (stat (fich,&s)==-1 || (df=open(fich,O_RDONLY))==-1)
        return ((ssize_t)-1);
    if (n==LEERCOMPLETO)
        tam=(ssize_t) s.st_size;
    if ((nleidos=read(df,p, tam))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return ((ssize_t)-1);
    }
    close (df);
    return (nleidos);
}

void * MmapFichero (char * fichero, int protection)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    if (protection&PROT_WRITE) modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
        return NULL;
/*Guardar Direccion de Mmap (p, s.st_size,fichero,df......);*/
    return p;
}

void Mmap (char *str, char* str2, char *fich) /*arg[0] is the file name
and arg[1] is the permissions*/
{
    char *perm;
    void *p;
    int protection=0;
    if (strcmp(str,"-free")!=0)
    {/*Listar Direcciones de Memoria mmap;*/ return;}
    if (strcmp(str2,"perm")!=0 && strlen(perm)<4) {
        if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
        if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if ((p=MmapFichero(str,protection))==NULL){
        perror ("Imposible mapear fichero");
    }
    

    else{
        printf ("fichero %s mapeado en %p\n", str, p);
    }

}

void * ObtenerMemoriaShmget (key_t clave, size_t tam)
{ /*Obtienen un puntero a una zaona de memoria compartida*/
/*si tam >0 intenta crearla y si tam==0 asume que existe*/
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    if (tam) /*si tam no es 0 la crea en modo exclusivo
esta funcion vale para shared y shared -create*/
        flags=flags | IPC_CREAT | IPC_EXCL;
/*si tam es 0 intenta acceder a una ya creada*/
    if (clave==IPC_PRIVATE) /*no nos vale*/
    {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
    return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno; /*si se ha creado y no se puede mapear*/
        if (tam) /*se borra */
            shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
/* Guardar En Direcciones de Memoria Shared (p, s.shm_segsz, clave.....);*/
    return (p);
}

void SharedCreate (char *str, char *str2) /*arg[0] is the key
and arg[1] is the size*/
{
    key_t k;
    size_t tam=0;
    void *p;
    if (str==NULL || str2==NULL ) {/*Listar Direcciones de Memoria Shared */ // return;}
    }
    k=(key_t) atoi(str);
    if (str2!=NULL)
        tam=(size_t) atoll(str2);
    if ((p=ObtenerMemoriaShmget(k,tam))==NULL)
        perror ("Imposible obtener memoria shmget");
    else
        printf ("Memoria de shmget de clave %d asignada en %p\n",k,p);
}
void SharedDelkey (char *str) /*arg[0] points to a str containing the key*/
{
    key_t clave;
    int id;
    char *key=str;
    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf (" shared -delkey clave_valida\n");
        return;
    }
    if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
}

void dopmap () /*no arguments necessary*/
{ pid_t pid; /*ejecuta el comando externo pmap para */
    char elpid[32]; /*pasandole el pid del proceso actual */
    char *argv[3]={"pmap",elpid,NULL};
    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap");
        exit(1);
    }
    waitpid (pid,NULL,0);
}

/*
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
*/