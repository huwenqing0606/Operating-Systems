#include "kernel/types.h"
#include "user/user.h"

int
main(){
    //if (fork()==0){
    //    write(1, "hello ", 6);
    //    exit(0);
    //} else {
    //    wait((int *) 0);
    //    write(1, "world\n", 6);
    //    exit(0);
    //}
    int fd;
    fd = dup(1);
    write(1, "hello ", 6);
    write(fd, "world\n", 6);
    exit(0);
}