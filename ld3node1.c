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
 
 
void* kp_test_openw(const char *name);
int kp_test_close(int fd);
 
int kp_test_getcwd();
 
int kp_test_getcwd(){
   char *cwd;
   cwd = getcwd( NULL, pathconf( ".", _PC_PATH_MAX) );
   puts( cwd );
   free( cwd );
   return 1;   
}
 
 
void* kp_test_openw(const char *name){
   void *dskr = NULL;
   dskr = dlopen( name, RTLD_LAZY | RTLD_LOCAL );
   if( dskr == NULL ){
      puts( dlerror());
      exit( 1 );
   }
   return dskr;
}
 
 
int main( int argc, char * argv[] ){
    void *d1;
    struct stat status;
    long lSize;
    char * buffer;
    size_t result;
    double *pd;
    if( argc < 2 ){
    printf( "Netinkamai pasirinkti duomenys", argv[0] );
    exit( 255 );
    }
    d1 = kp_test_openw(argv[1]);
    if(d1!=NULL) {
        printf("%s - failas. ", argv[1]);
        stat(argv[1], &status);
        printf("Jo i-node: %ld\n", status.st_ino);
        if(argc>2){
            int a;
            for(a=2; a < argc; a=a+1)
            {
                pd = dlsym( d1, argv[a]);
                if( pd == NULL ){
                    printf("simbolio: '%s' bibliotekoje nėra\n", argv[a]);
                    exit(1);
                }
                else printf("simbolio: '%s' adresas: %p \n",argv[a],pd);
            }
        }
    }
    dlclose(d1);
    printf( "(C) 2017, Jonas Lankelis %s\n", __FILE__ );
   
    return 0;
}
