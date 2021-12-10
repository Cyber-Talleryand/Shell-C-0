//
// Created by t_hss3 on 29/11/21.
//

#include "process.h"

void save_job_data(char* cpid){

}


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
    waitpid(fork(), &wstts, 0);
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

int entorno(char *str, char **env){
    
    if(is_comm_void(str))
        for(int i = 0; env[i] != NULL; i++)
            printf("%s\n", env[i]);
    else if(is_comm_equals(str, "-environ"))
        for(int i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
    else if(is_comm_equals(str, "-addr")){
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
            printf("%s guardada en %p(%p)", env[i], env[i], &env[i]);
            notFound = false;
        }
    if(notFound)
        printf("No existe '%s' en entorno", str);
    return 0;
}

int cambiarvar(tList L, char** env){
    if(count_node(L) != 3)
        return 2;
    char *newVar = strcat(strcat(L->next->data, "="), L->next->next->data);
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

void set_prio_aux(int who, int prio){
    setpriority(PRIO_PROCESS, who, prio);
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

int Senal(char * sen) /*devuel el numero de senial a partir del nombre*/
{
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}
char *NombreSenal(int sen) /*devuelve el nombre senal a partir de la senal*/
{ /* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
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
    else if(is_comm_equals(comm,"fgpri"))foregroundpri(argv,PL);
    else if(is_comm_equals(comm,"backpri"))backgroundpri(argv,PL);
    else if(is_comm_equals(comm, "ejec")) ejec(argv,PL);
}

void ejec(char* argv[]){
    execvp(argv[0], argv);
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
void foregroundpri(char* argv[],pidList *L){
    set_prio_aux(pid(NULL),-20);
    foreground(argv);
    set_prio_aux(pid(NULL),0);
}
void backgroundpri(char* argv[], pidList *L){
    set_prio_aux(pid(NULL),-20);
    background(argv,L);
    set_prio_aux(pid(NULL),0);
}

void printlistpid1(pidList *L){
    pidPos p;
    int sstatus,value;
    char* stop[1];
    char* pidaux="0000000";
    for(p=*L;p!=NULL;p=p->next){
        //kill(p->data.pid,SIGSTOP);
        if(waitpid(p->data.pid,&sstatus,WNOHANG | WUNTRACED | WCONTINUED)==p->data.pid){
            //put else if for prio

            printf("pid %i: prio: %d user: %s command: %s time: %d:%d:%d",p->data.pid,
                   getpriority(PRIO_PROCESS,p->data.pid),
                   /*getuid()*/"a",p->data.commmandline,p->data.time1.tm_hour,
                   p->data.time1.tm_min,p->data.time1.tm_sec);
            printf("status: %s", NombreSenal(sstatus));
            getchar();
            if(waitpid(p->data.pid,NULL, WIFEXITED(sstatus))) {
                p->data.val=waitpid(p->data.pid,NULL, WEXITSTATUS(sstatus));
                printf("value: %i", p->data.val );
            }

          //  kill(p->data.pid,SIGCONT);
        }

        //continue command

    }

}
void borrarjobs1(char* command, pidList *L){
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
}
void main_job(char *arg, char* cpid, pidList *L){
    long pid= str_to_int(cpid,NULL);
    pidPos item,save;
    if(is_comm_void(cpid) || (item=findItemPid((int)pid,*L))==PLNULL){
        printlistpid1(L);
    }
    else if(is_comm_void(arg)){
        save=item->next;
        item->next=PLNULL;
        printlistpid1( &item);
        item->next=save;
    }
    else if(is_comm_equals(arg,"-fg") && !is_comm_void(cpid)){
        foreground(&cpid);
    }
}

//traer proceso hacie delante

//por que kill en listjobs