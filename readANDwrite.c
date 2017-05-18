#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<aio.h>
#include<unistd.h>
#include<sys/mman.h>
#include <stdlib.h>
#include<fcntl.h>
 
int main( int argc, char *argv[]) {
 
  char *path = argv[1];
  int a = atoi(argv[3]);
  char buf[a];
  size_t nbytes;
  ssize_t bytes_read;
  ssize_t bytes_written;
 
  char *path2 = argv[2];
  int flag = O_RDONLY;
  int flag2 = O_WRONLY | O_CREAT | O_TRUNC;
 
  int d = open(path,flag);
  nbytes = sizeof(buf);
  bytes_read = read(d,buf,nbytes); 
  int d2 = open(path2,flag2);
  bytes_written = write(d2,buf ,nbytes);
  close(d);
  close(d2);
  return 0;
 
}
