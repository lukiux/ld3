#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>

void listdir(const char *name, int level)
{
        DIR *dir;
        struct dirent *entry;

        dir = opendir(name);
        if(dir==NULL){
                perror("opendir() failed");
                exit(1);
        }
        if(!(entry = readdir(dir)))
                return;
        do {
                        int status;
                        struct stat buffer;
                        status = stat(entry->d_name, &buffer);
                        if(status==-1){
                                 perror("stat() failed");
                                 exit(1);
                        }
                        if(S_ISREG(buffer.st_mode)){
                         if(buffer.st_size >= 1048576)
                                        chmod(entry->d_name,S_IRWXU);
                        }
                else if (S_ISDIR(buffer.st_mode)){
                        char path[1024];
                        int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
                        path[len] = 0;
                        int status;
                        struct stat buffer;
                        status = stat(entry->d_name, &buffer);
                        if(S_ISREG(buffer.st_mode)){
                                if(buffer.st_size >= 1048576)
                                        chmod(entry->d_name,S_IRWXU);
                       }
                        listdir(path,level+1);
                        }
        } while((entry = readdir(dir)) != NULL);
        closedir(dir);
}
int main(int argc, char *argv[]){
        listdir(".", 0);
        return 0;
}

