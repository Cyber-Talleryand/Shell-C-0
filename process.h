//
// Created by t_hss3 on 29/11/21.
//

#ifndef SHELL_PROCESS_H
#define SHELL_PROCESS_H
#include <sys/resource.h>
#include "commands.h"
#include "procc_list.h"
#include <unistd.h>
#include <signal.h>
#include <wait.h>
extern char **environ;
struct SEN{
    char *nombre;
    int senal;
};
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

int priority(tList L);
int doFork();
int rederr(char *str);
int entorno(char *str, char **env);
int mostrarvar(char *str, char **env);
int precambiarvar(tList L, char **env);
int cambiarvar(tList L, char **env);
//bool saveinfopid(int pid, pidList *L);
void argument_distribution(char *comm,tList L,pidList *PL);
void foreground(char* argv[]);
void background(char* argv[], pidList *L);
void foregroundpri(char* argv[], pidList *L);
void backgroundpri(char* argv[], pidList *L);
void printlistpid(pidList *L);
void borrarjobs(char* command, pidList *L);
void main_job(char *arg, char* cpid, pidList *L);
#endif //SHELL_PROCESS_H
