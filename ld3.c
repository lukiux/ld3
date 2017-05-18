/* Lukas Guzauskas IFF-5/1 lukguz */
/* Failas: lukguz_ld3.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
int checkIfDynamicLibrary(char *name){

        //dlclose(handle);
        //Dar neveikia
                void *d1;
                char buf[100];
                sprintf(buf,"./%s",name);
                d1 = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
                if( d1 != NULL ){
                        return 1;
                }
puts(dlerror());
return 0;
}

int checkIfElf(char *name){
        //Stub
//              ssize_t bytes_read;
  //              char buf[0];
    //            size_t nbytes;
      //          nbytes = sizeof(buf);
        //        bytes_read = read(ffd, buf, 124);
          //      if (fstat(ffd,&statbuf) == 0 && statbuf.st_size < 5) {
            //            printf("%s:(ELF failas) %jd  \n", dp->d_name, (intmax_t)statbuf.st_size);
              //  }

        return 1;
}

int main( int argc, char *argv[] ){
if( argc != 2){
        perror("Riba");
        exit(255);
}
int status;
struct stat buffer;
status = stat(argv[1], &buffer);
if (S_ISDIR (buffer.st_mode)){
     status = 0;
}
else{
        perror("Nera katalogo");
        exit(1);
}
struct aiocb aior;
   printf(" (C)2017 Lukas Guzauskas, %s\n", __FILE__);
   if(status == 0){
        DIR *d;
        struct dirent *dp;
        int dfd, ffd;
        struct stat statbuf;
        FILE *entry_file;
        d = opendir(argv[1]);
chdir(argv[1]);
        while ((dp = readdir(d)) != NULL){
         if (dp->d_name[0] == '.')
                        continue;
                status = stat(dp->d_name, &buffer);
                if (S_ISREG (buffer.st_mode))
                        status = 0;
                if (status == 0){
                        if(checkIfDynamicLibrary(dp->d_name) == 0){
                                printf("%s : dinamine biblioteka\n", dp->d_name);
                        }
                        if(checkIfElf(dp->d_name) == 0){
                                printf("%s: (ELF FAILAS)", dp->d_name);
                        }else {
                                int dskr;
 dskr = open(dp->d_name, O_RDONLY);
                                if(dskr == -1){
                                perror(dp->d_name);
                                exit(1);
                                }
                                char buff[10];
                                read(dskr, buff, 10);
                                printf("%s:", dp->d_name);
                                int i;
                                for(i = 0; i != 10; i = i + 1)
                                {
                                        printf("%d  ",buff[i]);
                                }
                                 printf("\n");
                        }
                }

        }
        closedir(d);
}
  return 0;
}

