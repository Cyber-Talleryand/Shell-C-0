//
// Created by t_hss3 on 10/12/21.
//

#include "procc_list.h"

void createEmptyListPid (pidList* L){
    *L=PLNULL;
}

int count_nodePid(pidList L){
    pidPos p;
    int i=0;
    for(p=L;p!=PLNULL;p=p->next)i++;
    return i-1;
}


/*En la declaración del nodo, se utiliza un puntero al cual le asignamos el espacio de memoria del struct y devuelve
un puntero no nulo.*/
bool createNodePid (pidPos* p){
    *p=malloc(sizeof(job));
    return *p!=PLNULL;
}

/*Tras comprobar si el nodo auxiliar ha sido creado correctamente, se posiciona el item en el lugar correspondiente.*/
bool insertItemPid(jobdata pid, pidList* L ){
    pidPos q;
    if(!createNodePid(&q)){
        return false;
    }
    else{
        q->data=pid;
        q->next=NULL;
        /*Si la lista esta vacía se inserta el item en la primera posición.*/
        if(*L==PLNULL) *L=q;

        else{
            lastPid(*L)->next=q;
        }

    }
    return true;
}



/*Se recorre la lista para encontrar el elemento requerido.*/
pidPos findItemPid(pid_t pid, pidList L) {

    pidPos p = L;
    /*Se comprueba si la lista está vacía, en caso afirmativo  */
    if (isEmptyListPid(L)) return PLNULL;
    else {
        //Se comprueba que el elemento siguiente al actual no sea nulo para simplificar la ejecución de la búsqueda
        if (p->next != PLNULL) {
            //Se recorre toda la lista buscando el elemento que coincida
            for(p=L;p != PLNULL && p->data.pid==pid;p=p->next);
            //Se comprueba si se ha llegado al final de la lista, en caso afirmativo se devuelve "nulo"
            if (p != PLNULL) {
                //Se comprueba si la posición obtenida si lo que contiene concuerda con lo que estamos buscando
                if (pid==p->data.pid)return p;
                    //en caso contrario se devuelve  que la posición es "nula"
                else return PLNULL;
            } else return PLNULL;
        }
            //Si solo hay un elemento en la lista se comprueba si este es el que buscamos
        else if (p->data.pid==pid) return p;
            //En caso de no cumplirse nada de lo anterior se devuelve posición nula
        else return PLNULL;
    }
}

/*Se comprueba si la lista esta vacía.*/
bool isEmptyListPid(pidList L){
    //Se devuelve el booleano de la condición necesaria de lista vacía
    return (L==PLNULL);
}

/*Se escoge el elemento de la posición introducida.*/
pid_t getItemPid(pidPos p, pidList L){
    if (!isEmptyListPid(L)) return p->data.pid;
    else return PNULL;
}

/*Devuelve la posición del primer elemento de la lista.*/
pidPos firstPid(pidList L){
    return L;
}

/*Devuelve la posición del último elemento de la lista.*/
pidPos lastPid(pidList L){
    pidPos p;
    // se comprueba si la lista está vacía
    if (isEmptyListPid(L))return PLNULL;

    //Posteriormente se recorre la lista hasta alcanzar el último elemento
    for (p = L;  p->next != PLNULL; p = p->next);
    return p;
}

/*Devuelve la posición del primer elemento anterior de la lista que no sea  el primero, ya que en cuyo caso devuelve
un NULL.*/
pidPos previousPid(pidPos p, pidList L){
    //Se comprueba que la posición y lista introducidas sean válidas y adicionalmente se comprueba que estos 2 no sean iguales
    if (L==p || p==PLNULL ||isEmptyListPid(L)){
        return  PLNULL;
    }
    else{
        pidPos q;
        for (q=L;q->next!=p;q=q->next);
        return q;
    }
}

/*Libera la memoria que ocupa la lista si no está vacía*/
void deleteListPid(pidList* L){
    pidPos p;
    /*Recorre toda la lista por punteros eliminando cada uno de ellos teniendo en cuenta que el último valor alcanzado de
     * "*L" es "nulo" y por ello no es necesario eliminarlo y además queda con el valos que indica que la lista está vacía,
     * no siendo necesario el comando createEmptyList para darle los valores correctos*/

    while(*L!=PLNULL){
        p=*L;
        *L=(*L)->next;
        free(p);
    }

};

void print_listPid(pidList L,int i){
    pidPos aux; int a=0;
    for(aux=L;aux!=PLNULL && a<i;aux=aux->next){
        a++;
        printf("%d-> %i\n",a, aux->data.pid);
    }
}

void deleteAtPositionPid(pidPos p, pidList *L){
    pidPos c;
    if(p==PLNULL) return;
    c=previousPid(p,*L);
    if(c==PLNULL){
        (*L)=(*L)->next;
    }
    else c->next=p->next;
    free(p);
}
void deleteListPidCond(pidList *L,int comm, int arg, int arg2 ){
    pidPos p;
    if(comm==1){
        for(p=*L;p!=NULL;p=p->next){
            if(p->data.status==arg) deleteAtPositionPid(p,L);
        }
    }
    if(comm==2){
        for(p=*L;p!=NULL;p=p->next){
            if(p->data.status==arg || p->data.status==arg2) deleteAtPositionPid(p,L);
        }
    }

}
