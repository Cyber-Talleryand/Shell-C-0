#ifndef DYNAMIC_LIST_H          //Comprobamos si "DYNAMIC_LIST_H" no está definida.
#define DYNAMIC_LIST_H          //Definición de una contante simbólica "DYNAMIC_LIST_H".

#include <stdbool.h>            //Añadimos el contenido de la librería "stdbool.h".
#include <string.h>             //Añadimos el contenido de la librería "string.h".
#include <stdlib.h>             //Añadimos el contenido de la librería "stdlib.h".

#define LNULL NULL              //Definición de una contante simbólica "LNULL" con valor nulo, es decir 0.
#define MAXTAML 100


typedef struct tNode* tPosL;                        //Declaración de un tipo de dato denominado "tPosl", de tipo "struct tNode*".

typedef tPosL tList;                                //Declaración de un tipo de dato denominado "tList", de tipo "struct tNode*".

struct tNode{                                       //Declaración de una estructura con una variable "struct(tItemL)" denominada "data" y otra
    char data[MAXTAML];                                    //variable "tPosL" que es un puntero a un nodo denominado "next".
    tPosL next;
};




void createEmptyList(tList* L);                     //Crea una lista vacía.
bool createNode (tPosL* L);                         //Se utiliza un puntero al cual le asignamos, el tamaño del struct.
bool insertItem(char d[], tList* L);                //Se posiciona el item en el lugar correspondiente.
bool copyList(tList L, tList* M);                   //Pasa una copia de la lista copiada y la dirección de la lista a copiar.
void updateItem(char d[] , tPosL p, tList* L);      //Modifica el contenido del elemento situado en la posición indicada.
void deleteAtPosition(tPosL p, tList* L);           //Libera la memoria que ocupa una posición de la lista.
void deleteList(tList* L,bool a);                          //Libera la memoria que ocupa la lista.
tPosL findItem(char d[], tList L);               //Devuelve la posición del primer elemento de la lista cuyo nick de usuario
// se corresponda con el indicado (o LNULL si no existe tal elemento).
bool isEmptyList(tList L);                          //Determina si la lista está vacía.
char* getItem(tPosL p, tList L);                   //Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
tPosL first(tList L);                               //Devuelve la posición del primer elemento de la lista.
tPosL last(tList L);                                //Devuelve la posición del último elemento de la lista.
tPosL previous(tPosL p, tList L);                   //Devuelve la posición en la lista del elemento anterior al de la posición
// indicada (o LNULL si la posición no tiene anterior).
tPosL next(tPosL p, tList L);                       //Devuelve la posición en la lista del elemento siguiente al de la posición
// indicada (o LNULL si la posición no tiene siguiente).
void print_list(tList L, int i);
void print_lista(tList L);
void inPrintList(tList L, char c[]);
void multitouni(tList *L);

#endif
