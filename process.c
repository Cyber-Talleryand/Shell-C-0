//
// Created by t_hss3 on 10/12/21.
//
#include "process.h"

#define MAXPATHLENGTH 9999

int rederr(char *str){
    if(strcmp(str, FIN_COMM)==0){
        char newpath[999];
        readlink("/proc/self/fd/2", newpath, 999);
        printf("%s", newpath);
    }else if(strcmp(str, "-reset")==0)
        dup2(1, 2);
    else{
        int fd = open(str, O_WRONLY);
        if(fd == -1)
            perror("Cannot redirect errors");
        else
            dup2(fd, 2);
    }return 0;
}

int doFork(){
    int wstts;
    int pid;
    if((pid = fork()) == 0)
        printf("Nuevo proceso: %d\n", getpid());
    else
        waitpid(pid, &wstts, 0);
    return 0;
}

int priority(tList L){
    if(strcmp(L->data, FIN_COMM) == 0)
        printf("Shell priority: %d\n", getpriority(PRIO_PROCESS, getpid()));
    else if(strcmp(L->next->data, FIN_COMM) == 0)
        printf("%ld priority: %d\n", strtol(L->data, NULL, 10), getpriority(PRIO_PROCESS, strtol(L->data, NULL, 10)));
    else
        setpriority(PRIO_PROCESS, strtol(L->data, NULL, 10), strtol(L->next->data, NULL, 10));
    return 0;
}

int uid(tList L){
    if((strcmp("-get", L->data) * strcmp(FIN_COMM, L->data)) == 0)
        uidGet();
    else if(strcmp("-set", L->data) == 0)
        if(strcmp("-l", L->next->data) == 0)
            uidSetU(L->next->next->data);
        else
            uidSetId(strtol(L->next->next->data, NULL, 10));
    else
        return 2;
    return 0;
}

void uidGet(){
    printf("Real user: %s(ID: %d)\n", getpwuid(getuid())->pw_name, getuid());
    printf("Effective user: %s(ID: %d)\n", getpwuid(geteuid())->pw_name, geteuid());
}

void uidSetU(char *user){
    if(setuid(getpwnam(user)->pw_uid) != 0)
        perror("Cambio no válido");
}

void uidSetId(int uid){
    if(setuid(uid) != 0)
        perror("Cambio no válido");
}

int entorno(char *str, char **env){
    if(strcmp(str, FIN_COMM) == 0)
        for(int i = 0; env[i] != NULL; i++)
            printf("%s\n", env[i]);
    else if(strcmp(str, "-environ") == 0)
        for(int i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
    else if(strcmp(str, "-addr") == 0){
        printf("environ = %p guardada en %p\n", environ, &environ);
        printf("arg3 = %p guardada en %p\n", env, &env);
    }else
        return 2;
    return 0;
}

int mostrarvar(char *str, char **env){
    bool notFound = true;
    if(strcmp(str, FIN_COMM) == 0)
        return 2;
    for(int i = 0; env[i] != NULL; i++)
        if(strncmp(str, env[i], strlen(str)) == 0){
            printf("argc3-> %s guardada en %p(%p)\n\t", env[i], env[i], &env[i]);
            notFound = false;
        }
    if(notFound){
        printf("No existe '%s' en entorno", str);
        return 0;
    }
    for(int i = 0; env[i] != NULL; i++)
        if(strncmp(str, env[i], strlen(str)) == 0){
            printf("environ-> %s guardada en %p(%p)\n\t\t", environ[i], environ[i], &environ[i]);
            notFound = false;
        }
    char *aux = getenv(str);
    printf("getenv-> %s guardada en %p", aux, aux);
    return 0;
}

int cambiarvar(tList L, char** env){
    if(count_node(L) != 3)
        return 2;
    char *aux = strcat(L->next->data, "=");
    char *newVar = (char*)malloc(strlen(L->next->data)+strlen(L->next->next->data)+2);
    strcpy(newVar, aux);
    strcat(newVar, L->next->next->data);
    if(strcmp(L->data, "-e") == 0){
        for(int i = 0; environ[i] != NULL; i++)
            if(strncmp(L->next->data, environ[i], strlen(L->next->data)) == 0)
                strcpy(environ[i], newVar);

    }else if(strcmp(L->data, "-a") == 0){
        for(int i = 0; env[i] != NULL; i++)
            if(strncmp(L->next->data, env[i], strlen(L->next->data)) == 0)
                strcpy(env[i], newVar);
    }else if(strcmp(L->data, "-p") == 0){
        if(putenv(newVar) != 0)
            perror("Cambio no posible");
    }else
        return 2;
    return 0;
}

int preEjecNo(tList L, void (*fEjec)(prious, char *, char**, char*, char**)){
    if(count_node(L) < 1)
        return 2;
    char** vars = malloc(sizeof(char)*(count_node(L)-1));
    char** args = malloc(sizeof(char)*(count_node(L)-1));
    vars[0] = "\0";
    args[0] = "\0";
    int i = 0;
    tPosL p, temp;
    for(p = L; p->data[0] < 97; p = p->next, i++)
        vars[i] = p->data;
    vars[i] = NULL;
    for(temp = p->next, i = 0; strcmp(temp->next->data, FIN_COMM) != 0; temp = temp->next, i++)
        args[i] = temp->data;
    args[i] = NULL;
    fEjec(NO, p->data, vars, p->data, args);
    free(vars);
    free(args);
    return 0;
}

int preEjecPrious(tList L, void (*fEjec)(prious, char*, char**, char*, char**)){
    if(count_node(L) < 2)
        return 2;
    char** vars = malloc(sizeof(char)*(count_node(L)-1));
    char** args = malloc(sizeof(char)*(count_node(L)-1));
    vars[0] = "\0";
    args[0] = "\0";
    int i = 0;
    tPosL p, temp;
    for(p = L->next; p->data[0] < 97; p = p->next, i++)
        vars[i] = p->data;
    for(temp = p->next, i = 0; strcmp(temp->next->data, FIN_COMM); temp = temp->next, i++)
        args[i] = temp->data;
    if(L->data[strlen(p->data)-2] = 'r')
        fEjec(PRIO, L->data, vars, p->data, args);
    else
        fEjec(USER, L->data, vars, p->data, args);
    free(vars);
    free(args);
    return 0;
}

char *ejecutable (char *s){
    char path[MAXPATHLENGTH];
    static char aux2[MAXNAMLEN];
    struct stat st;
    char *p;
    if (s==NULL || (p=getenv("PATH"))==NULL)
        return s;
    if (s[0]=='/' || !strncmp (s,"./",2) || !strncmp (s,"../",3))
        return s; //is an absolute pathname
    strncpy (path, p, MAXPATHLENGTH);
    for (p=strtok(path,":"); p!=NULL; p=strtok(NULL,":")){
        sprintf (aux2,"%s/%s",p,s);
        if (lstat(aux2,&st)!=-1)
            return aux2;
    }
    return s;
}

int execvpe(char *file, char *const argv[], char *const envp[]){
    return execve(ejecutable(file),argv, envp);

}

void ejec(prious tipo, char* val, char** vars, char* prog, char** args){
    switch(tipo){
        case PRIO:{
            setpriority(PRIO_PROCESS, getpid(), strtol(val, NULL, 10));
            break;
        }
        case USER:{
            uidSetU(val);
            break;
        }
        case NO:
        default: break;
    }
    if(vars == NULL)
        vars = environ;
    if(execvp(prog, args) == -1)
        perror("No se ha podido ejecutar el programa");
}



bool saveinfopid(int pid,char* exec, pidList *L){
    char save;
    strcpy(&save,exec);
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
    struct jobdata d;
    d.pid=pid;
    d.commmandline=&save;
    d.time1=tm;
    return insertItemPid(d,L);
}

void argument_distribution(char *comm,tList L,pidList *PL){
    tPosL p;
    char *argv[3]={
            "/bin/bash",
            "-c",
            L->next->data,
    };


    for(p=L->next->next; !is_comm_void(p->data);p=p->next){
        strcat(argv[2], " ");
        strcat(argv[2],p->data);
    }

    if(is_comm_equals(comm,"fg"))foreground(argv);
    else if(is_comm_equals(comm,"back"))background(argv,PL);
    else if(is_comm_equals(comm, "ejec")) ejec1(argv);
}

void argument_distribution_plus(char *comm,tList L,pidList *PL) {
    tPosL p;
    char *argv[3]={
            "/bin/bash",
            "-c",
            L->next->next->data,
    };


    for(p=L->next->next->next; !is_comm_void(p->data);p=p->next) {
        strcat(argv[2], " ");
        strcat(argv[2],p->data);

    }

    if(is_comm_equals(comm,"fgpri"))foregroundpri(L->next->data,argv,PL);
    else if(is_comm_equals(comm,"backpri"))backgroundpri(L->next->data,argv,PL);
    else if(is_comm_equals(comm,"ejecas"))ejecas1(L->next->data,argv,PL);
    else if(is_comm_equals(comm,"ejecpri"))ejecpri1(L->next->data,argv,PL);
    else if(is_comm_equals(comm,"backas"))backgroundas(L->next->data,argv,PL);
    else if(is_comm_equals(comm,"fgas"))foregroundas(L->next->data,argv,PL);
}



void ejec1(char* argv[]){
    execvp(argv[0], argv);
}
void ejec_fin(tList L, pidList *PL){
    tPosL p;
    char *argv[3]={
            "/bin/bash",
            "-c",
            L->data,
    };


    for(p=L->next; !is_comm_void(p->data);p=p->next) {
        strcat(argv[2], " ");
        strcat(argv[2],p->data);

    }
    background(argv,PL);
}

void foreground(char* argv[]){
    int pid1;
    if((pid1=fork())==0) {
        execvp(argv[0], argv);
    }
    waitpid(pid1,NULL,0);
}

void background(char* argv[], pidList *L){
    int pid1;
    if((pid1=fork())==0){
        execvp(argv[0],argv);
        //guardar info de background
        exit(0);
        //borrar info background
    }
    saveinfopid(pid1,argv[2],L);
    //guardar


}
void set_prio_aux(int who, int prio){
    setpriority(PRIO_PROCESS, who, prio);
}
void foregroundpri(char* prio,char* argv[],pidList *L){
    long i;
    int b;
    b= getpriority(PRIO_PROCESS, getpid());
    i=str_to_int(prio,NULL);
    set_prio_aux(pid(NULL),i);
    foreground(argv);
    set_prio_aux(pid(NULL),b);


}

void backgroundpri(char* prio,char* argv[], pidList *L){
    long i;
    int b;
    b= getpriority(PRIO_PROCESS, getpid());
    i=str_to_int(prio,NULL);
    set_prio_aux(pid(NULL),i);
    background(argv,L);
    set_prio_aux(pid(NULL),b);
}
void ejecpri1(char *prio,char* argv[], pidList* L){
    long i;
    int b;
    b= getpriority(PRIO_PROCESS, getpid());
    i=str_to_int(prio,NULL);
    set_prio_aux(pid(NULL),i);
    ejec1(argv);
    set_prio_aux(pid(NULL),b);
}
char * NombreUsuario (uid_t uid)
{
    struct passwd *p;
    if ((p=getpwuid(uid))==NULL)
        return (" ??????");
    return p->pw_name;
}
uid_t UidUsuario (char * nombre)
{
    struct passwd *p;
    if ((p=getpwnam (nombre))==NULL)
        return (uid_t) -1;
    return p->pw_uid;
}
void CambiarUidLogin (char * login)
{
    uid_t uid;
    if ((uid=UidUsuario(login))==(uid_t) -1){
        printf("loin no valido: %s\n", login);
        return;
    }
    if (setuid(uid)==.1)
        printf ("Imposible cambiar credencial: %s\n", strerror(errno));
}

void ejecas1(char *user,char* argv[], pidList *L){
    uid_t save;
    save=getuid();
    CambiarUidLogin(user);
    ejec1(argv);
    CambiarUidLogin(NombreUsuario(save));
}
void backgroundas(char *user,char* argv[], pidList *L){
    uid_t save;
    save=getuid();
    CambiarUidLogin(user);
    background(argv,L);
    CambiarUidLogin(NombreUsuario(save));
}
void foregroundas(char *user,char* argv[], pidList *L){
    uid_t save;
    save=getuid();
    CambiarUidLogin(user);
    foreground(argv);
    CambiarUidLogin(NombreUsuario(save));
}

int Senal(char * sen) /*devuel el numero de senial a partir del nombre*/{
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}

char *NombreSenal(int sen) /*devuelve el nombre senal a partir de la senal*/{ /* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}

void printlistpid(pidList *L){
    pidPos p;
    int sstatus,value;
    char* stop[1];
    int pidaux;
    for(p=*L;p!=NULL;p=p->next){


        pidaux = waitpid( p->data.pid, &sstatus, WNOHANG|WUNTRACED|WCONTINUED);
        if (pidaux > 0)
        {
            printf("pid %i: prio: %d user: %s command: %s time: %d:%d:%d",p->data.pid,
                   getpriority(PRIO_PROCESS,p->data.pid),
                    //getuid()
                   "a"
                    ,p->data.commmandline,p->data.time1.tm_hour,
                   p->data.time1.tm_min,p->data.time1.tm_sec);
            printf("status: %s", NombreSenal(sstatus));
            if (WIFEXITED(sstatus)) {
                printf("Child exited with RC=%d\n",WEXITSTATUS(sstatus));
            }
            if (WIFSIGNALED(sstatus)) {
                printf("Child exited via signal %d\n",WTERMSIG(sstatus));
            }
        }
        /*stop[0]="kill -stop ";
        sprintf(pidaux,"%d",p->data.pid);
        strcat(*stop,pidaux);
        //foreground(stop);
        if(waitpid(p->data.pid,&sstatus,WNOHANG | WUNTRACED | WCONTINUED)==p->data.pid){
            //put else if for prio

            printf("pid %i: prio: %s user: %s command: %s time: %li",p->data.pid,
                    *//*getpriority(PRIO_PROCESS,p->data.pid)"a",*/
                    /*getuid()*/ //"a"/ ,p->data.commmandline,p->data.time1);
            /*printf("status: %s", NombreSenal(sstatus));
            if(waitpid(p->data.pid,NULL, WIFEXITED(sstatus))) {
                p->data.val=waitpid(p->data.pid,NULL, WEXITSTATUS(sstatus));
                printf("value: %i", p->data.val );
            }
            stop[0]="kill -cont ";
            sprintf(pidaux,"%d",p->data.pid);
            strcat(*stop,pidaux);*/
        };

        //continue command

    }

/*
int listjobs(pidList pL){
	printlistpid(&pL);
	return 0;
}*/

int borrarjobs(char* command, pidList *L){
    if(is_comm_equals(command,"-term")){
        deleteListPidCond(L,0,SIGTERM,0);
    }
    if(is_comm_equals(command,"-sig")){
        deleteListPidCond(L,0,SIGKILL,0);
    }
    if(is_comm_equals(command,"-clear")){
        deleteListPidCond(L,1,SIGKILL,SIGTERM);
    }
    if(is_comm_equals(command,"-all")){
        deleteListPid(L);
    }
    return 0;
}

void main_job(char *arg, char* cpid, pidList *L){
    long pid= str_to_int(cpid,NULL);
    pidPos item,save;
    if(is_comm_void(cpid) || (item=findItemPid((int)pid,*L))==PLNULL){
        printlistpid(L);
    }
    else if(is_comm_void(arg)){
        save=item->next;
        item->next=PLNULL;
        printlistpid( &item);
        item->next=save;
    }
    else if(is_comm_equals(arg,"-fg") && !is_comm_void(cpid)){
        foreground(&cpid);
    }
}

