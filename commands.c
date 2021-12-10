//
// Created by T_hss3 on 15/11/21.
//

#include "commands.h"

bool is_comm_void(char* str){
    if (str==NULL || strcmp(str,FIN_COMM)==0) return true;
    return false;
}
bool is_comm_equals(char* str, char* str2){
    if (strcmp(str,str2)==0) return true;
    return false;
}
void limpiar_string(char* string, int c){
    for(int i = 0; i < c && string[i]!='\0'; i++){
        string[i] = '\0';
    }
}

void str_to_cmm(char /* * */str[], tList* comm) {
    char c, an_str[MAXTAML];
    int aux = 0;
    for(int i = 0; str[i]!='\0'; i++){
        c = str[i];
        if(c == ' '){
            an_str[aux] = '\0';
            insertItem(an_str, comm);
            limpiar_string(an_str,i);
            aux = 0;
        }else if ((c>=65 && c<=90) || (c>=97 && c<=122) || c==45){
            an_str[aux] = c;
            aux++;
        }
    }
    insertItem(an_str, comm);
    insertItem(FIN_COMM,comm);
}

long str_to_int(char* str, char* rubbish){
    long i;
    i= strtol(str,&rubbish,10);
    return i;
}


void obt_com(tList* comm) {
    char c, an_str[MAXTAML];
    bool status_comm=true;
    int i = 0;

    limpiar_string(an_str,MAXTAML);
    printf("\n>>");

    do {
        c = getchar();
        if (i >= MAX_COMM || c == EOF || c == '\n') {
            status_comm = false;
            an_str[i] = '\0';
            insertItem(an_str, comm);
        } else if(c == ' '){
            an_str[i] = '\0';
            insertItem(an_str, comm);
            limpiar_string(an_str,i);
            i = 0;
        }else{
            an_str[i] = c;
            i++;
        }
    } while (status_comm);
    insertItem(FIN_COMM, comm);
}



int autores(char *str){

    if (is_comm_void(str) ){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
        printf("r.d.gmantuano@udc.es\t\t\t");
        printf("david.alvarez.celemin@udc.es\n");
    }
    if (is_comm_equals(str, "-l")){
        printf("Rodrigo Dantes Gonzalez Mantuano\t");
        printf("David Álvarez Celemín\n");
    }
    if (is_comm_equals(str, "-n")) {
        printf("r.d.gmantuano@udc.es\t");
        printf("david.alvarez.celemin@udc.es\n");
    }
    return 0;
}
int fecha(char *str){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if(is_comm_equals(str,"-d"))printf("%d-%02d-%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    else if(is_comm_equals(str,"-l"))printf("%02d:%02d:%02d",tm.tm_hour, tm.tm_min, tm.tm_sec);
    else if(is_comm_void(str))printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,tm.tm_hour, tm.tm_min, tm.tm_sec);
    return 0;
}
int infosis(){
    struct utsname aux;
    uname(&aux);
    printf("%s",aux.sysname);
    return 0;
}
int pid(char *str){
    if(is_comm_equals(str, "-p"))
        printf("Parent_PID Terminal: %d\n",getppid());
    else if(is_comm_void(str))
        printf("PID Terminal: %d\n",getpid());
    else
        printf("Incorrect argument (check the documentation)");
    return 0;

}
int historial(char *str,tList *L){
    int i;
    if(is_comm_void(str))
        print_list(*L, MAX_COMM);
    else if(is_comm_equals(str, "-c"))
        deleteList(L);
    else if(strcmp(str, "0")>=0 && atoi(str)<=999){
        i=strtol(str, NULL, 10);
        print_list(*L, i);
    }
    else return 1;
    return 0;
}
int carpeta (char str[]){
    if(is_comm_void(str)){
        getpwd();
        return 0;
    }
    else if(chdir(str)==0){
        printf("Movido a %s",str);
    }
    else perror("Directorio no válido");
    printf(" ");
    return 0;
}
int getpwd(){
    char aux[60];
    getcwd(aux, MAX_COMM);
    printf("%s\n",aux);
    return 0;
}
tPosL comando(char *str, tList L) {
    tPosL p;
    int a, i = 0;
    a = atoi(str);
    a--;
    for (p = L; p != NULL && i < a; p = p->next) {
        i++;
    }

    if (a <= i) {
        printf("(*) %s\n", p->data);
        return p;
    }
    else return NULL;
}


int ayuda(char *str){
    if(is_comm_equals(str,"pid")) ayuda_pid();
    if(is_comm_equals(str,"autores")) ayuda_autores();
    if(is_comm_equals(str,"fecha")) ayuda_fecha();
    if(is_comm_equals(str,"infosis")) ayuda_infosis();
    if(is_comm_equals(str,"hist")) ayuda_historial();
    if(is_comm_equals(str,"ayuda")) ayuda_ayuda();
    if(is_comm_equals(str,"carpeta")) ayuda_carpeta();
    if(is_comm_equals(str,"comando")) ayuda_comando();
    if (is_comm_equals(str, "fin") || is_comm_equals(str, "salir") || is_comm_equals(str, "bye")==0) ayuda_salir();
    return 0;
}
void ayuda_comando(){
    printf("Reutiliza el comando del historial correspodiente al número intrducido");
}
void ayuda_pid(){
    printf("Muestra el PID del programa\n En caso de pasar el parámetro -p se muestra el del proceso padre");
}
void ayuda_autores(){
    printf("Muestra los datos de los autores\n\"-l\"para solo ver los correos\n\"-n\" para solo los nombres de los creadores");
}
void ayuda_fecha(){
    printf("Muestra la fecha y la hora del sistema por defecto\n\"-d\" para solo ver la fecha");
}
void ayuda_infosis(){
    printf("Muestra la información del sistema operativo\n");
}
void ayuda_historial(){
    printf("Muestra los comandos utilizados anteriormente\n\"-N\" Muestra solo los N primero elementos \n\"-c\"Resetea la tabla");
}
void ayuda_ayuda(){
    printf("Muestra la documentación de los comandos");
}
void ayuda_carpeta(){
    printf("Redirige el shell del directorio actual al directorio destino");
}
void ayuda_salir(){
    printf("Saca al usuario de la shell");
}
void ayuda_crear(){
    printf("Crea directorio en la carpeta actual\n "
           "Si se usa la opción \"-f\" se crea un fichero en lugar de un directorio");
}

void ayuda_listfich(){
    printf("Imprime la información de los archivos que van a continuación del comando\n"
           "\"-long\" amplía la información sobre los archivos"
           "\"-link\" muestra la relación simbólica con otros archivos"
           "\"-acc\" substituye la fecha de última modificación por la de último acceso"
           "Si no hay parámetros imprime la dirección del directorio actual\n"
           "");
}
void ayuda_listdir(){
    printf(" ");
}
void ayuda_borrar(){
    printf("Borra los archivos o directorios vacíos indicados");
}
void ayuda_borrarrec(){
    printf("Borra los directorios o archivos de forma recursiva");
}








void get_parameters(tList *L, tList M){
    tPosL p;
    for(p=M;p!=NULL && p->data[0]=='-';p=p->next){
        insertItem(p->data,L);
    }
}

void an_list(tList* L,tList *temp,void (*function)(struct stat stats, tList *temp, char* name)) {
    tList p;
    struct stat structstat;
    get_parameters(temp, *L);
    if (isEmptyList(*temp)) p = *L;
    else p = findItem(last(*temp)->data, *L)->next;
    for (; p != NULL && !is_comm_void(p->data); p = p->next) {
        if (stat(p->data, &structstat) == 0) {
            (*function)(structstat, temp, p->data);
        }
    }
    deleteList(temp);
}

void list_to_array(tList L, char* argv[]){
    tPosL p;
    int i=0;
    for(p=L; is_comm_void(p->data);p=p->next){
        argv[i]=p->data;
        i++;
    }
}
