/*
 * Rodrigo Gonzalez Mantuano r.d.gmantuano@udc.es
 *
 * David Alvarez Celemin
 *
 * */

//#include "func.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "memory_list.h"
#include "commands.h"
#include "memory_func.h"
#include "storage_mod.h"
#include "process.h"


#define MAX_AUX_COMM 20
#define LEERCOMPLETO ((ssize_t)-1)



bool an_comm(tList L, tList *historia, MemList *dynamic_memory, pidList *PL, bool check);


int main(){
    char aux[MAXTAML];
    tList hist, comando;
    MemList dynamic_memory;
    pidList PL;
    bool status=true;
    createEmptyList(&hist);
    createEmptyMemoList(&dynamic_memory);
    createEmptyListPid(&PL);


    do {
        createEmptyList(&comando);
        obt_com(&comando);
        inPrintList(comando,aux);
        insertItem(aux,&hist);
        status=an_comm(comando, &hist, &dynamic_memory,&PL,true);
        deleteList(&comando);
        printf("\n");
        limpiar_string(aux,MAXTAML);
    }while(status);
    deleteList(&hist);
    deleteListMemo(&dynamic_memory);
    deleteListPid(&PL);
}


bool an_comm(tList L, tList *historia, MemList *dynamic_memory, pidList *PL, bool check){
    int a=1;
    tList temp;
    createEmptyList(&temp);
    if(is_comm_equals(L->data,"pid")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=pid(L->next->data);
    }
    else if(is_comm_equals(L->data,"autores")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=autores(L->next->data);

    }
    else if(is_comm_equals(L->data,"fecha")){
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=fecha(L->next->data);
    }
    else if(is_comm_equals(L->data,"infosis")) {
        if(count_node(L->next)>0){
            check=false;
            a=2;
        }
        else a=infosis();
    }
    else if(is_comm_equals(L->data,"hist")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a= historial(L->next->data,historia);
    }
    else if(is_comm_equals(L->data,"ayuda")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else
            a=ayuda(L->next->data);
    }
    else if(is_comm_equals(L->data,"carpeta")) {
        if(count_node(L->next)>1){
            check=false;
            a=2;
        }
        else a=carpeta(L->next->data);
    }
    else if(is_comm_equals(L->data,"crear")) a= crear(L->next);
    else if(is_comm_equals(L->data,"listfich")) a= list_fich(L->next,&temp);
    else if(is_comm_equals(L->data,"listdir")) a= list_dir_up(L->next, &temp);
    else if(is_comm_equals(L->data,"borrar")) a= borrar(L->next);
    else if(is_comm_equals(L->data,"borrarrec")) a= borrarrec(L->next);
    else if(is_comm_equals(L->data,"malloc")){
        if(count_node(L->next)==0){
            malloc_general(FIN_COMM,FIN_COMM,dynamic_memory);
        }
        else if(count_node(L->next)==1){
            malloc_general(FIN_COMM,L->next->data,dynamic_memory);
        }

        else if(count_node(L->next)==2){
            malloc_general(L->next->data,L->next->next->data,dynamic_memory);
        }
    }
    else if(is_comm_equals(L->data,"dealloc")){
        if(count_node(L->next)==0){
            dealloc(FIN_COMM,NULL,dynamic_memory);
        }
        if(count_node(L->next)==1){
            dealloc(FIN_COMM,&L->next,dynamic_memory);
        }
        else if(count_node(L->next)==2){
            dealloc(L->next->data,&L->next->next,dynamic_memory);
        }
    }
    else if(is_comm_equals(L->data,"shared")){

        if((a=count_node(L->next))==0){
            main_shared(FIN_COMM,FIN_COMM,FIN_COMM,dynamic_memory);
        }
        else if(a==1){
            main_shared(FIN_COMM,L->next->data,NULL,dynamic_memory);
        }
        else if(a==2 || a==3){
            main_shared(L->next->data,L->next->next->data,L->next->next->next->data,dynamic_memory);
        }
    }
    else if(is_comm_equals(L->data,"mmap")){
        if(count_node(L->next)==0){
            Mmap(FIN_COMM,FIN_COMM,FIN_COMM,dynamic_memory);
        }
        if (count_node(L->next)==2){

            if(is_comm_equals(L->next->data,"-free")){
                Mmap(L->next->data,NULL,L->next->next->data,dynamic_memory);
            }
            else{
                Mmap(L->next->data,L->next->next->data,L->next->data,dynamic_memory);
            }
            //Mmap(L->next->data,L->next->next->data,L->next->next->next->data,dynamic_memory);
            //Mmap(L->next->next->data,L->next->next->next->data,L->next->data,dynamic_memory);
        }
    }

    else if(is_comm_equals(L->data,"recursiva")){
        doRecursiva(L->next->data);
    }

    else if(is_comm_equals(L->data,"memoria")) a= prememoria(L->next, (MemList)*dynamic_memory);
        //else if(is_comm_equals(L->data,"recursiva")) a= prerrecursiva(L->next->data);
    else if(is_comm_equals(L->data,"llenarmem")) a= prellenarmem(L->next);
    else if(is_comm_equals(L->data,"volcarmem")) a= prevolcarmem(L->next);
    else if(is_comm_equals(L->data,"e-s")) a= esBase(L->next);
    else if((is_comm_equals(L->data,"priority"))) priority(L->next);
    else if((is_comm_equals(L->data,"fg")||is_comm_equals(L->data,"back")))
        argument_distribution(L->data,L,PL);
    else if((is_comm_equals(L->data,"fgas")||is_comm_equals(L->data,"backas")
             || is_comm_equals(L->data,"fgpri")) || is_comm_equals(L->data,"backpri"))
        argument_distribution_plus(L->data,L,PL);

    else if (is_comm_equals(L->data,"entorno")){
        if(count_node(L->next)==0){
            entorno(NULL,environ);
        }
        else if(count_node(L->next)==1)entorno(L->next->data,environ);

            //Aqui hay que revisar
        else entorno(L->next->data,/*(L->next->next)->data)*/environ);
    }
    else if(is_comm_equals(L->data, "borraarjobs"))borrarjobs(L->next->data,PL);
    else if (is_comm_equals(L->data,"listjobs"))printlistpid(PL);
    else if(is_comm_equals(L->data,"job")) {
        if(count_node(L->next)==0){
            main_job(NULL,NULL,PL);
        }
        else if(count_node(L->next)==1){
            main_job(NULL,L->next->data,PL);
        }
        else if(count_node(L->next)==2){
            main_job(L->next->data,L->next->next->data,PL);
        }
    }
    else if(is_comm_equals(L->data,"comando")) {
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
                an_comm(aux, historia, dynamic_memory, PL,  false);
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
