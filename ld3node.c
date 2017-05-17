#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>
 
int (*fptr)(const char *s);
 
int main (int argc, char *argv[])
{
printf("(C) 2016 L.Guzauskas\n");
void *dl;
int pd;
struct stat fileStat;
if(stat(argv[1],&fileStat) < 0){
        printf("pateikas pirmasis argumentas nera failas\n");
        return 1;
}
printf("%s  - Failas. " ,argv[1]);
printf("Jo i-node: \t\t%d\n",fileStat.st_ino);
   dl = dlopen( argv[1], RTLD_LAZY | RTLD_LOCAL );
printf("Likusiu argumentu adresu spausdinimas\n");
int i;
for(i = 2; i < argc; i++)
{
        *(void**)(&fptr) = dlsym( dl,argv[i] );
        if (fptr == NULL)
        {
                printf("Simbolio %s bibliotekoje nera\n",argv[i]);
        }
        else
        {
                printf("Simbolio %s adresas: %p\n",fptr, (void*) &fptr);
        }
}
        return 0;
}
