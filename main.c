#include "func.h"
/*@Alvaro revisa si el cambio char *str => char *str[] es correcto*/
int main(){
    char aux[MAXTAML];
    tList hist, comando;
    MemList dynamic_memory;
    createEmptyList(&hist);
    createEmptyMemoList(&dynamic_memory);
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


bool an_comm(tList L, tList *historia, MemList *dynamic_memory,bool check){
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
    if(is_comm_equals(L->data,"malloc")){
        if(count_node(L->next)==2){
            malloc_general(FIN_COMM,L->next->data,dynamic_memory);
        }
        else if(count_node(L->next)==3){
            malloc_general(L->next->data,L->next->next->data,dynamic_memory);
        }
    }
    if(is_comm_equals(L->data,"dealloc")){
        if(count_node(L->next)==2){
            dealloc(FIN_COMM,&L->next,dynamic_memory);
        }
        else if(count_node(L->next)==3){
            dealloc(L->next->data,&L->next->next,dynamic_memory);
        }
    }



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