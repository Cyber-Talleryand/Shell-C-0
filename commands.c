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



bool an_comm(tList L, tList *historia, tList *dynamic_memory,bool check){
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
    printf("");
}
void ayuda_borrar(){
    printf("Borra los archivos o directorios vacíos indicados");
}
void ayuda_borrarrec(){
    printf("Borra los directorios o archivos de forma recursiva");
}






char LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

