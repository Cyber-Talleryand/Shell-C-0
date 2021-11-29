//
// Created by t_hss3 on 29/11/21.
//

#ifndef SHELL_PROCCESS_H
#define SHELL_PROCCESS_H
#include <sys/resource.h>
#include "commands.h"
#include "procc_list.h"
#include <unistd.h>
extern char **environ;;

void priority(char *cpid, char *cvalue);
void env();
#endif //SHELL_PROCCESS_H
