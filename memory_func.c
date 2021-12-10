//
// Created by t_hss3 on 17/11/21.
//

#include "memory_func.h"
int v1,v2,v3;

void malloc_general(char *str, char *size, MemList *dynamic_register){
    long i;
    char *rubbish;
    MemPos p;
    struct tMemory *item;
    if(is_comm_void(size)){
        for(p=*dynamic_register;p!=NULL;p=p->next){
            if(p->typeId==memo)printf("%p: size:%ld. malloc %d-%02d-%02d \n",p->memdir,p->size,p->date.tm_year+1900,p->date.tm_mon,p->date.tm_mday);
        }

    }
    i=str_to_int(size, rubbish);
    if(is_comm_void(str)){
        if(i>0){
            description description1;
            item=createItemMemo(i);
            modifyItem(item,memo,description1);
            insertItemMemo(item,dynamic_register);
        }


        return;
    }
    else if(is_comm_equals(str,"-free")){
        deleteFromMemoryGeneral((int)i,dynamic_register);
        return;
    }
    else{
        perror("Parámetros introducidos incorrectos");
    }
}

void dealloc(char *str, tList* list_memo, MemList* L){

    tPosL p=NULL;
    if(is_comm_equals(str,"-malloc") && is_comm_void(str)){
        for(p=*list_memo;p!=NULL;p=p->next){
            deleteFromMemoryGeneral((int) str_to_int(p->data,NULL),L);
        }
    }
    else if(is_comm_equals(str,"-shared")){
        for(p=*list_memo;p!=NULL;p=p->next){
            deleteFromMemoryShared(str_to_int(p->data,NULL),L);
        }
    }
    else if(is_comm_equals(str,"-mmap")){
        for(p=*list_memo;p!=NULL;p=p->next){
            deleteFromMemoryMmap(p->data,L);
        }
    }
    else if(is_comm_void(str) && list_memo!=NULL &&!is_comm_void((*list_memo)->data)){
        MemPos f;
        void* i;
        char* rubbish;
        for(p=*list_memo;p!=NULL&& strcmp(p->data,FIN_COMM)!=0;p=p->next){
            i= (void *) str_to_int_base(p->data,rubbish,16);
            f= findDirMemo(i,*L);
            if(f!=NULL){
                deleteAtPositionMemo(f,L);
            }
        }
    }
    else if(is_comm_void(str)){
        MemPos f;
        for(f=*L;f!=NULL;f=f->next){
            if(f->typeId==memo)printf("%p: size:%ld. malloc %d-%02d-%02d \n",f->memdir,f->size,f->date.tm_year+1900,f->date.tm_mon,f->date.tm_mday);
            else if(f->typeId==shared)printf("%p: size:%ld. shared memory (key %i) %d-%02d-%02d \n",f->memdir,f->size,f->info.key,f->date.tm_year+1900,f->date.tm_mon,f->date.tm_mday);
            else if(f->typeId==mmap_id)printf("%p: size:%ld. mmap %s (fd %i) %d-%02d-%02d \n",f->memdir,f->size,f->info.file.filename,f->info.file.fd,f->date.tm_year+1900,f->date.tm_mon,f->date.tm_mday);
        }
    }
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam, MemList* L)
{ /*Obtienen un puntero a una zaona de memoria compartida*/
/*si tam >0 intenta crearla y si tam==0 asume que existe*/
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    struct tMemory* item;
    description description;
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
    item=createItemMemo((long int)tam);
    description= createDescriptorShared(clave);
    modifyItem(item,shared,description);
    insertItemMemo(item,L);
/* Guardar En Direcciones de Memoria Shared (p, s.shm_segsz, clave.....);*/
    return (p);
}

bool SharedCreate (char *str, char *str2,MemList* L){
    /*arg[0] is the key
and arg[1] is the size*/
    key_t k;
    size_t tam=0;
    void *p;
    if (str==NULL || str2==NULL ) {
        print_memory_list(*L);
        return true;
    }
    k=(key_t) atoi(str);
    if (str2!=NULL)tam=(size_t) atoll(str2);
    if ((p=ObtenerMemoriaShmget(k,tam,L))==NULL){
        perror ("Imposible obtener memoria shmget");
        return false;
    }
    else{
        printf ("Memoria de shmget de clave %d asignada en %p\n",k,p);
        return true;
    }

}


void SharedDelkey (char *str) /*arg[0] points to a str containing the key*/{
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

    if (shmctl(id,IPC_RMID,NULL)==-1) {
        perror("shmctl: imposible eliminar memoria compartida\n");
        return;
    }
    printf("Key:%i elimminada",clave);


}

void main_shared(char* str,char* key, char* tam, MemList* L){
    MemPos p;
    if(is_comm_equals(str,"-create")){
        struct tMemory* item;
        description description1;
        if(SharedCreate(key,tam,L)){
            item=createItemMemo(str_to_int(tam,NULL));
            description1=createDescriptorShared((int)str_to_int(key,NULL));
            modifyItem(item,shared,description1);
            insertItemMemo(item,L);
        }
    }
    else if(is_comm_equals(str,"-delkey")){
        SharedDelkey(key);
    }
    else if(is_comm_equals(str,"-free")){

        deleteFromMemoryShared(str_to_int(key,NULL),L);
    }
    else if(is_comm_void(str) && !is_comm_void(key)){
        for(p=*L;p!=NULL;p=p->next){
            if(p->typeId==shared && p->info.key== str_to_int(key,NULL))printf("Allocated shared memory (key %i) at %p",p->info.key,p->memdir);
        }

    }
    else if(is_comm_void(str)){
        for(p=*L;p!=NULL;p=p->next){
            if(p->typeId==shared)printf("%p: size:%ld. malloc %d-%02d-%02d \n",p->memdir,p->size,p->date.tm_year+1900,p->date.tm_mon,p->date.tm_mday);
        }
    }


}


void * MmapFichero (char * fichero, int protection,MemList *L)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    struct tMemory* item;
    description descriptor;
    if (protection&PROT_WRITE) modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
        return NULL;
/*Guardar Direccion de Mmap (p, s.st_size,fichero,df......);*/
    item=createItemMemo(s.st_size);
    descriptor=createDescriptormmap(df,fichero);
    modifyItem(item,mmap_id,descriptor);
    insertItemMemo(item,L);
    return p;
}

void Mmap (char *str, char* str2, char *fich, MemList *L) {
    /*arg[0] is the file name
and arg[1] is the permissions*/
    MemPos f;
    if(is_comm_void(fich)){
        for(f=*L;f!=NULL;f=f->next){
            if(f->typeId==mmap_id)printf("%p: size:%ld. mmap %s (fd %i) %d-%02d-%02d \n",f->memdir,f->size,f->info.file.filename,f->info.file.fd,f->date.tm_year+1900,f->date.tm_mon,f->date.tm_mday);
        }
        return;
    }
    if (str!=NULL && is_comm_equals(str,"-free")){
        deleteFromMemoryMmap(fich,L);
        return;
    }
    void *p;
    int protection=0;

    if (strcmp(str2,"perm")!=0 && strlen(str2)<4) {
        if (strchr(str2,'r')!=NULL) protection|=PROT_READ;
        if (strchr(str2,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(str2,'x')!=NULL) protection|=PROT_EXEC;
    }

    if ((p=MmapFichero(str,protection,L))==NULL){
        perror ("Imposible mapear fichero");
    }
    else{
        printf ("fichero %s mapeado en %p\n", str, p);
    }

}


void dopmap () /*no arguments necessary*/{ pid_t pid; /*ejecuta el comando externo pmap para */
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



long str_to_int_base(char* str, char* rubbish, int base){
    long i;
    i= strtol(str,&rubbish,base);
    return i;
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

int prevolcarmem(tList L){
    if(strcmp(L->next->data, FIN_COMM) == 0)
        volcarmem(L->data, 25);
    else
        volcarmem(L->data, strtol(L->next->data, NULL, 10));
    return 0;
}

void volcarmem(char *dir, int n){
    char *p;
    int j, t;
    char abajo[25];
    sscanf(dir, "%p", &p);
    printf("Volcando %d bytes de memoria desde %s", n, dir);
    for(int i = 0; i < n; i+=j){
        t = 0;
        for(j = 0; j < 25 && i+j < n; j++){
            if(*p < 32)
                printf("  ");
            else
                printf("  %c", *p);
            abajo[j] = *p;
            t++;
            p++;
        }
        printf("\n");
        for(int w = 0; w < t; w++)
            printf(" %x", abajo[w]);
        printf("\n");
    }
}

int prellenarmem(tList L){
    if(strcmp(L->next->data, FIN_COMM) == 0)
        llenarmem(L->data, 128, "A");
    else if(strcmp(L->next->next->data, FIN_COMM) == 0)
        llenarmem(L->data, strtol(L->next->data, NULL, 10), "A");
    else
        llenarmem(L->data, strtol(L->next->data, NULL, 10), L->next->next->data);
    return 0;
}

void llenarmem(char *dir, int n, char *byte){
    char *aux;
    char *p;
    char by = strtol(byte, &aux, 0);
    if(by == 0)
        by = *aux;
    sscanf(dir, "%p", &p);
    printf("Llenando %d bytes con %c desde %p", n, by, p);
    for(int i = 0; i < n; i++){
        *p = by;
        p++;
    }
}

int esBase(tList L){
    if(strcmp(L->data, FIN_COMM) == 0)
        return 2;
    else if(strcmp(L->data, "read") == 0)
        return preRead(L->next);
    else if(strcmp(L->data, "write") == 0)
        return preWrite(L->next);
    else
        return 1;
}

int preRead(tList L){
    if(count_node(L) < 2)
        return 2;
    es_read(L->data, L->next->data, strtol(L->next->next->data, NULL, 10));
    return 0;
}

int preWrite(tList L){
    int i = 3;
    bool overwrite = false;
    if(strcmp(L->data, "-o") == 0){
        i = 4;
        overwrite = true;
    }
    if(count_node(L) < i)
        return 2;
    es_write(L->data, L->next->data, strtol(L->next->next->data, NULL, 10), overwrite);
    return 0;
}

void es_read(char *fich, char *dir, int n){
    int fd = open(fich, O_RDONLY);
    if(fd == -1){
        perror(fich);
        return;
    }
    if(n == 0){
        struct stat structstat;
        if(fstat(fd, &structstat) != 0){
            perror(fich);
            return;
        }
        n = structstat.st_size;
    }
    char *p;
    sscanf(dir, "%p", &p);
    read(fd, p, n);
}

void es_write(char *fich, char *dir, int n, bool o){
    if(!o){
        int f2;
        f2 = open(fich, O_WRONLY);
        close(f2);
        if(f2 != -1)
            return;
    }
    int fd = open(fich, O_CREAT|O_WRONLY);
    if(fd == -1){
        perror(fich);
        return;
    }
    char *p;
    sscanf(dir, "%p", &p);
    write(fd, p, n);
}


void recursiva_bottom (int n)
{
    char automatico[TAMANO];
    static char estatico[TAMANO];
    printf ("parametro n:%d en %p\n",n,&n);
    printf ("array estatico en:%p \n",estatico);
    printf ("array automatico en %p\n\n",automatico);
    n--;
    if (n>0)
        recursiva_bottom(n);
}

void doRecursiva(char* n){
    recursiva_bottom((int)str_to_int(n,NULL));
}

int prememoria(tList L, MemList M){
    bool blocks = true, vars = true, funcs = true, pmap = true;
    if(strcmp(L->data, FIN_COMM) == 0 || findItem("-all", L) != NULL);
    else {
        if(findItem("-blocks", L) == NULL)
            blocks = false;
        if(findItem("-vars", L) == NULL)
            vars = false;
        if(findItem("-funcs", L) == NULL)
            funcs = false;
        if(findItem("-pmap", L) == NULL)
            pmap = false;
    }
    memoria(blocks, vars, funcs, pmap, M);
    return 0;
}

void memoria(bool b, bool v, bool f, bool p, MemList mL){
    if(b)
        print_memory_list(mL);
    if(v){
        int l1 = 0, l2 = 0, l3 = 0;
        static int s1 = 0, s2 = 0, s3 = 0;
        v1=0;v2=0;v3=0;
        printf("\nVariables globales en: \t%p %p %p\nVariables estáticas en:\t%p %p %p\nVariables locales en: \t%p %p %p\n",
               &v1, &v2, &v3, &s1, &s2, &s3, &l1, &l2, &l3);
    }
    if(f)
        printf("\nFunciones en %p, %p y %p\n\n", autores, fecha, infosis);
    if(p)
        dopmap();
}
