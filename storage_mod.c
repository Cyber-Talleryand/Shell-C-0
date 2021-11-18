//
// Created by t_hss3 on 17/11/21.
//

#include "storage_mod.h"

int crear(tList L){
    tList p;
    bool a = false;
    if(is_comm_equals(L->data,"-f")){
        a = true;
        L = L-> next;
    }
    for(p=L; !is_comm_void(p->data);p=p->next)
        crear_x(p, a);
    return 0;
}

int crear_x(tList L, bool cond){
    FILE *fp;
    if (cond){
        if((fp=fopen(L->data,"r"))!= NULL) {
            printf("Cannot create that file, already exists");
            fclose(fp);
        }
            //Posible perdida de puntero
        else{
            //fclose(fp);
            if((fp=fopen(L->data,"w"))==NULL){
                printf("Cannot create that file");
            }
            else fclose(fp);
        }
    }else if (mkdir(L->data, 0777) == -1)
        printf("Error al crear el directiorio");
    else
        printf("Directory created %s",L->data);
    return 0;
}

void printFileProperties(struct stat stats, tList *temp,char* name){
    struct tm dt;
    if(!(name[0] == '.' && findItem("-hid",*temp)==NULL)){
        if(findItem(FIN_COMM,*temp)==NULL/*|| findItem("-long",temp)==NULL && findItem("-link",temp)!=NULL*/){
            if(findItem("-acc",*temp)!=NULL){
                // File modification time
                dt = *(gmtime(&stats.st_mtime));
                printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                       dt.tm_hour, dt.tm_min, dt.tm_sec);
            } else{
                dt = *(gmtime(&stats.st_ctime));
                printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                       dt.tm_hour, dt.tm_min, dt.tm_sec);

            }
            // Get file creation time in seconds and
            // convert seconds to date and time format
            if(findItem("-long",*temp)){

                printf("%lu\t%ld\t",stats.st_nlink,stats.st_ino);

                if (stats.st_mode &  S_IRUSR)
                    printf("r ");
                if (stats.st_mode & S_IWUSR)
                    printf("w ");
                if (stats.st_mode & S_IXUSR)
                    printf("x");
                printf("\t");

            }
            if(findItem("-link",*temp)!=NULL) sym_link();

        }


        // File size
        printf("%ld\t", stats.st_size);
        printf("%s\t",name);
        printf("\n");
    }
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
char * ConvierteModo (mode_t m, char *permisos)
{
    strcpy (permisos,"---------- ");
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r'; /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r'; /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r'; /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s'; /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';
    return permisos;
}


void sym_link (){

    char linkname[MAX_MID];
    char cwd[MAX_MID];


    if(getcwd(cwd,sizeof(cwd))!=NULL){
        ssize_t r = readlink(cwd, linkname, MAX_MID);

        if (r != -1) {
            linkname[r] = '\0';
            printf(" -> %s\t", linkname);
        }
        else
            printf("none\t");
    }

}

int list_fich(tList L, tList *temp){
    if(is_comm_void(L->data)) {
        getpwd();
        return 0;
    }
    createEmptyList(temp);
    an_list(&L,temp,&printFileProperties);
    deleteList(temp);
    return 0;
}


int list_dir_up(tList L, tList *temp){
    if(is_comm_void(L->data))
        carpeta(FIN_COMM);
    else{
        createEmptyList(temp);
        an_list(&L, temp, &list_dir_bottom);
        deleteList(temp);
    }
    return 0;
}

void list_dir_bottom(struct stat structstat, tList *temp,char* name){
    struct dirent *de;
    DIR *dr = NULL;
    bool a=(S_ISDIR(structstat.st_mode)), b=(strcmp(name,".")!=0 && strcmp(name,"..")!=0);
    struct stat sub_structstat;
    char source[MAX_COMM];
    getcwd(source, MAX_COMM);
    //Si no es un directorio, imprime la información del archivo
    if(!a)
        printFileProperties(structstat,temp, name) ;
        //si es un directorio lo abre y recorre
    else if (a&&b){
        printf("\n%s->\n", name);
        if ((dr = opendir(name)) == NULL) {
            perror(name);
            return;
        }
        chdir(name);
        while ((de=readdir(dr))!=NULL){
            stat(de->d_name, &sub_structstat);
            list_dir_bottom(sub_structstat, temp, de->d_name);
        }
        closedir(dr);
        chdir(source);
    }
}

int borrar(tList L){
    if(is_comm_void(L->data)){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; is_comm_void(p->data); p = p->next){
            if(remove(p->data) != 0){
                perror(p->data);
                printf("\n");
            }
        }
        return 0;
    }
}
void rec(char *str){
    char source[MAX_COMM];
    getcwd(source, MAX_COMM);
    struct stat structstat;
    if(stat(str, &structstat) != 0)
        perror(str);
    /*if(LetraTF(structstat.st_mode) != 'd'){
        if(remove(str) != 0)
            perror(str);
        return;
    }*/
    DIR *dirp;
    struct dirent *e;
    errno = 0;
    if ((dirp = opendir(str)) == NULL)
        perror(str);
    else{
        chdir(str);
        while((e = readdir(dirp)) != NULL){
            if((strcmp(e->d_name, ".") * strcmp(e->d_name, "..")) != 0){
                if(remove(e->d_name) != 0)
                    rec(e->d_name);
                else
                    perror(e->d_name);
            }
        }
        chdir(source);
        if(remove(str) != 0)
            perror(str);
    }
}

int borrarrec(tList L){
    if(is_comm_void(L->data)){
        getpwd();
        return 0;
    }else{
        for(tPosL p = L; is_comm_void(p->data); p = p->next){
            if(remove(p->data) != 0){
                if(errno == 39)
                    rec(p->data);
                else
                    perror(p->data);
            }
        }
    }
    return 0;
}
