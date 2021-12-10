//
// Created by t_hss3 on 10/12/21.
//

#ifndef SHELL_PROCESS_H
#define SHELL_PROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>

#include "dynamic_list.h"
#include "commands.h"
#include "procc_list.h"

extern char** environ;

typedef struct SEN{
    char *nombre;
    int senal;
}SEN;

static struct SEN sigstrnum[]={
        "HUP", SIGHUP,
        "INT", SIGINT,
        "QUIT", SIGQUIT,
        "ILL", SIGILL,
        "TRAP", SIGTRAP,
        "ABRT", SIGABRT,
        "IOT", SIGIOT,
        "BUS", SIGBUS,
        "FPE", SIGFPE,
        "KILL", SIGKILL,
        "USR1", SIGUSR1,
        "SEGV", SIGSEGV,
        "USR2", SIGUSR2,
        "PIPE", SIGPIPE,
        "ALRM", SIGALRM,
        "TERM", SIGTERM,
        "CHLD", SIGCHLD,
        "CONT", SIGCONT,
        "STOP", SIGSTOP,
        "TSTP", SIGTSTP,
        "TTIN", SIGTTIN,
        "TTOU", SIGTTOU,
        "URG", SIGURG,
        "XCPU", SIGXCPU,
        "XFSZ", SIGXFSZ,
        "VTALRM", SIGVTALRM,
        "PROF", SIGPROF,
        "WINCH", SIGWINCH,
        "IO", SIGIO,
        "SYS", SIGSYS,
/*senales que no hay en todas partes*/
#ifdef SIGPOLL
        "POLL", SIGPOLL,
#endif
#ifdef SIGPWR
        "PWR", SIGPWR,
#endif
#ifdef SIGEMT
        "EMT", SIGEMT,
#endif
#ifdef SIGINFO
        "INFO", SIGINFO,
#endif
#ifdef SIGSTKFLT
        "STKFLT", SIGSTKFLT,
#endif
#ifdef SIGCLD
        "CLD", SIGCLD,
#endif
#ifdef SIGLOST
        "LOST", SIGLOST,
#endif
#ifdef SIGCANCEL
        "CANCEL", SIGCANCEL,
#endif
#ifdef SIGTHAW
        "THAW", SIGTHAW,
#endif
#ifdef SIGFREEZE
        "FREEZE", SIGFREEZE,
#endif
#ifdef SIGLWP
        "LWP", SIGLWP,
#endif
#ifdef SIGWAITING
        "WAITING", SIGWAITING,
#endif
        NULL,-1,
}; /*fin array sigstrnum */


typedef enum prious{PRIO, USER, NO}prious;

int priority(tList L);
int doFork();
int rederr(char *str);
int entorno(char *str, char **env);
int mostrarvar(char *str, char **env);
int cambiarvar(tList L, char **env);
int preEjecNo(tList L, void (*fEjec)(prious, char*, char**, char*, char**));
int preEjecPrious(tList L, void (*fEjec)(prious, char*, char**, char*, char**));
void ejec(prious tipo, char* val, char** vars, char* prog, char** arg);
void fg(prious tipo, char* val, char** vars, char* prog, char** arg);
void back(prious tipo, char* val, char** vars, char* prog, char** arg);
void ejecpri(prious tipo, char* val, char** vars, char* prog, char** arg);
void ejecas(prious tipo, char* val, char** vars, char* prog, char** arg);
void fgpri(prious tipo, char* val, char** vars, char* prog, char** arg);
void fgas(prious tipo, char* val, char** vars, char* prog, char** arg);
void backpri(prious tipo, char* val, char** vars, char* prog, char** arg);
void backas(prious tipo, char* val, char** vars, char* prog, char** arg);
int uid(tList L);
void uidGet();
void uidSetU(char *user);
void uidSetId(int uid);
int listjobs(pidList pL);
int borrarjobs(char* command, pidList *L);
int doJob(char *arg, char* cpid, pidList *L);
bool saveinfopid(int pid,char* exec, pidList *L);
void argument_distribution(char *comm,tList L,pidList *PL);
void foreground(char* argv[]);
void background(char* argv[], pidList *L);
void foregroundpri(char *prio,char* argv[], pidList *L);
void backgroundpri(char *prio,char* argv[], pidList *L);
void ejec1(char* argv[]);
void ejecas1(char *user,char* argv[], pidList *L);
void backgroundas(char *user,char* argv[], pidList *L);
void foregroundas(char *user,char* argv[], pidList *L);
void ejecpri1(char *prio,char* argv[], pidList *L);
void argument_distribution_plus(char *comm,tList L,pidList *PL);
void printlistpid(pidList *L);
void main_job(char *arg, char* cpid, pidList *L);
#endif //SHELL_PROCESS_H
