/* Lukas Adeikis IFF-5/1 lukade */
/* Failas: lukade_stat01.c */
 
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
int checkIfDirectory(char *dirName){
        int status;
        struct stat st_buf;
        status = stat (dirName, &st_buf);
        if (status != 0) {
                printf ("Error, errno = %d\n", errno);
                return 1;
        }
        if (S_ISDIR (st_buf.st_mode)) {
        printf ("%s yra direktorija.\n", dirName);
        }
        return 0;
}
 
int readDir(char* dirName){
        DIR *dir;
        struct dirent *dp;
        dir = opendir(dirName);
        printf ("%s failai.\n", dirName);
        chdir(dirName);
        while ((dp = readdir(dir)) != NULL){
                char* name;
                name = dp->d_name;
                int status;
                status = checkIfRegular(name, dirName);
                if(status == 0){
                        if(checkIfDynamicLibrary(name) == 0){
                        printf("%s : dinamine biblioteka\n", name);
                        }
                        if(checkIfElf(name) == 0){
                        printf("$s : (ELF FAILAS)", name);
                        } else {
                                printFileContents(name);
                        }
                }
        }
        closedir(dir);
        return 0;
}
 
int printFileContents(char *name){
        int fildes;
        fildes = open(name, O_RDONLY);
        if( fildes == -1 ){
        perror( name );
        exit(1);
        }
        char buff[10];
        read(fildes, buff, 10);
        printf("%s :", name);
        int i;
        for(i = 0; i != 10; i = i + 1)
        {
                printf("%d  ", buff[i]);
        }
        printf("\n");
        return 0;
}
 
int checkIfElf(char *name){
        //Stub
        return 1;
}
 
int checkIfRegular(char *name){
        int status;
        struct stat st_buf;
        status = stat (name, &st_buf);
        if (status != 0) {
                printf ("Error, errno = %d\n", errno);
                return 1;
        }
        if (S_ISREG (st_buf.st_mode)) {
                return 0;
        }
}
 
int checkIfDynamicLibrary(char *name){
        void *handle;
        //handle = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
        if (!handle) {
               return 1;
        }
        //dlclose(handle);
        //Dar neveikia
        return 1;
}
 
int main( int argc, char * argv[] ){
        printf( "(C) 2017 Lukas Adeikis, %s\n", __FILE__ );
        int dirCheck;
        dirCheck = checkIfDirectory(argv[1]);
        if(dirCheck == 0){
                readDir(argv[1]);
        }
        return 0;
}
