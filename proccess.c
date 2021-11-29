//
// Created by t_hss3 on 29/11/21.
//

#include "proccess.h"

void priority(char *cpid, char *cvalue){
    long pid,value;
    char *rubbish=NULL, *rubbish2=NULL;

    pid=str_to_int(cpid,rubbish);
    value= str_to_int(cvalue,rubbish2);
    if(rubbish==NULL && rubbish2==NULL){
        if(is_comm_void(cvalue) ){
            if(is_comm_void(cpid)) pid;
            else getpriority(PRIO_PROCESS,pid);
        }
        else{
            if(!is_comm_void(cpid)){
                setpriority(PRIO_PROCESS,pid,(int) value);
            }
        }
    }
};


void env(){
    char **env=environ;
    while (env!=NULL){
        printf("%s\n", *env++);
    }
}


struct jobdata{


    id_t pid;
    char*commmandline;
    time_t time1;
    int status;//runnind, exitted
    int val;//value of the programm

};

