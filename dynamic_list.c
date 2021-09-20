/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 3
 * AUTHOR 1: Rodrigo Dantés González Mantuano LOGIN 1: r.d.gmantuano@udc.es
 * AUTHOR 2: Angel Varela Sánchez LOGIN 2: angel.varela.sanchez@udc.es
 * GROUP: 1.4
 * DATE: 25/06/21
 */

#include <stdio.h>
#include "dynamic_list.h"

/*Para indicar las modificaciones con respecto al trabajo anterior, estas estarán indicadas con el sufijo "Mod R A"(Modificado Respecto al Anterior)*/

/*Pasa por puntero una lista y pone todos el valor nulo.*/
void createEmptyList (tList* L){
    *L=LNULL;
}


/*En la declaración del nodo, se utiliza un puntero al cual le asignamos el espacio de memoria del struct y devuelve
un puntero no nulo.*/
bool createNode (tPosL* p){
    *p=malloc(sizeof(struct tNode));
    return *p!=LNULL;
}

/*Tras comprobar si el nodo auxiliar ha sido creado correctamente, se posiciona el item en el lugar correspondiente.*/
bool insertItem(tItemL d, tList* L ){
    tPosL q, r;
    if(!createNode(&q)){
        return false;
    }
    else{
        q->data= d;
        q->next= LNULL;

        /*Si la lista esta vacía se inserta el item en la primera posición.*/
        if(*L==LNULL) *L=q;

            /*Si el elemento a introducir es mayor que el último de la lista, este se introduce al final*/
        else if(strcmp(d.nickname,getItem(last(*L),*L).nickname)>0){
            for(r=*L; r->next != LNULL; r=r->next);
            r->next=q;
        }
            /*Si el elemento a introducir es menor que el primero de la lista, el puntero "next" le damos el valor
             * del puntero inicial y renombramos como puntero incial al nuevo elemento*/
        else if(strcmp(d.nickname,getItem(first(*L),*L).nickname)<0){
            q->next=*L;
            *L=q;
        }
            /*Si no se cumple nada de lo anterior, recorremos la lista hasta que encontremos el elemento mayor(r) que el introducido en la función.
             *Después modificamos para que nuestro nuevo elemento(q), su variable "next", apunte al siguiente elemento al mayor(r) y que el "next"
             * de este último(r) apunte al nuevo elemento(q)*/
        else{
            for(r=*L;r!=LNULL && strcmp(getItem(next(r,*L),*L).nickname,d.nickname)<0;r=r->next);
            q->next=r->next;
            r->next=q;
        }
        return true;
    }
}

/*Se va a la posicion introducida para modificar el elemento que queremos.*/
void updateItem(tItemL d , tPosL p, tList* L){
    p->data=d;


}

/*Se recorre la lista para encontrar el elemento requerido.*/
tPosL findItem(tNickname d, tList L) {

    tPosL p = L;
    /*Se comprueba si la lista está vacía, en caso afirmativo  */
    if (isEmptyList(L)) return LNULL;
    else {
        //Se comprueba que el elemento siguiente al actual no sea nulo para simplificar la ejecución de la búsqueda
        if (p->next != LNULL) {
            //Se recorre toda la lista buscando el elemento que coincida
            for(p=L;p != LNULL && strcmp(p->data.nickname, d) != 0;p=p->next);
            //Se comprueba si se ha llegado al final de la lista, en caso afirmativo se devuelve "nulo"
            if (p != LNULL) {
                //Se comprueba si la posición obtenida si lo que contiene concuerda con lo que estamos buscando
                if (strcmp(p->data.nickname, d) == 0)return p;
                //en caso contrario se devuelve  que la posición es "nula"
                else return LNULL;
            } else return LNULL;
        }
        //Si solo hay un elemento en la lista se comprueba si este es el que buscamos
        else if (strcmp(p->data.nickname, d) == 0) return p;
        //En caso de no cumplirse nada de lo anterior se devuelve posición nula
        else return LNULL;
    }
}

/*Se comprueba si la lista esta vacía.*/
bool isEmptyList(tList L){
    //Se devuelve el booleano de la condición necesaria de lista vacía
    return (L==LNULL);
}

/*Se escoge el elemento de la posición introducida.*/
tItemL getItem(tPosL p, tList L){
    if (p!=LNULL) return p->data;
}

/*Devuelve la posición del primer elemento de la lista.*/
tPosL first(tList L){
    return L;
}

/*Devuelve la posición del último elemento de la lista.*/
tPosL last(tList L){
    tPosL p;
    // se comprueba si la lista está vacía
    if (isEmptyList(L))return LNULL;
    //Posteriormente se recorre la lista hasta alcanzar el último elemento
    for (p = L;  p->next != LNULL; p = p->next);
    return p;
}

/*Devuelve la posición del primer elemento anterior de la lista que no sea  el primero, ya que en cuyo caso devuelve
un NULL.*/
tPosL previous(tPosL p, tList L){
    //Se comprueba que la posición y lista introducidas sean válidas y adicionalmente se comprueba que estos 2 no sean iguales
    if (L==p || p==LNULL ||isEmptyList(L)){
        return  LNULL;
    }
    else{
        tPosL q;
        for (q=L;q->next!=p;q=q->next);
        return q;
    }
}

/*Devuelve el siguiente elemento de la lista.*/
tPosL next(tPosL p, tList L){
    if(p!=LNULL)return p->next;
    return LNULL;
}

/*Libera la memoria que ocupa una posición de la lista.*/
void deleteAtPosition(tPosL p, tList* L) {
    tPosL q;
    /*Si la posición que se quiere borrar es la primera, el siguiente elemento pasa a ser el primero.*/
    if (p != LNULL) {
        if (p == *L) *L = (*L)->next;
            /*Si la posición que se quiere borrar es la ultima, se recorre toda la lista hasta llegar al penuntimo elemento
            y ponerle el nodo nulo para desvincularlo del último que estaba anteriormente.*/
        else if (p->next == LNULL) {
            for (q = *L; q->next != p; q = q->next);
            q->next = LNULL;
        }
            /*Si no se cumple nada de  lo anterior, se desvincula la posición que queremos borrar de la lista y se vinculan
            las posiciones que estaban unidas a este.*/
        else {
            for(q=*L;q!=LNULL && q->next!=p;q=q->next);
            q->next=p->next;
        }
        free(p);
    }
}


/*Libera la memoria que ocupa la lista si no está vacía*/
void deleteList(tList* L){
    tPosL p;
    /*Recorre toda la lista por punteros eliminando cada uno de ellos teniendo en cuenta que el último valor alcanzado de
     * "*L" es "nulo" y por ello no es necesario eliminarlo y además queda con el valos que indica que la lista está vacía,
     * no siendo necesario el comando createEmptyList para darle los valores correctos*/
    while(*L!=LNULL){
        p=*L;
        *L=(*L)->next;
        free(p);
    }


};