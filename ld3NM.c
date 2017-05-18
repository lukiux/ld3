#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int darbas(const char *name, int N, int M);
int darbas(const char *name, int N, int M){
        int dskr;
        dskr = open(name, O_RDONLY);
        if(dskr == -1){
                perror("Nera failo");
                exit(1);
        }
int status;
char buffer[M];
struct stat buffe;
status = stat(name, &buffe);
if(read(dskr,buffer,M) < M){
        printf("Tiek faile nera, duomenu nuskaityti negalima, failas nebus kuriamas\n");
        exit(1);
}
if(lseek(dskr,N,SEEK_END) < 0){
        printf("Neatlinka");
        exit(1);
}
int dskr1;
ssize_t bytes_read;
dskr1=open("data.bin",O_WRONLY | O_CREAT | O_TRUNC, 0644);
bytes_read = write(dskr1, buffer, M);
printf("Failas data.bin duomenis sukurtas\n");
printf("%d", buffer[0]);
printf("%d", buffer[bytes_read - 1]);

return dskr;
}

int main(int argc, char *argv[]){
if(argc != 4){
        perror("Negali daugiau argumentu");
        exit(1);
}
        int d, N, M;
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        d = darbas(argv[1],1,100);
return 0;
}
