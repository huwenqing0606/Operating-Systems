#include "kernel/types.h"
#include "user/user.h"

void
main(){
    char buf[512];
    int n;
    for (;;){
        n = read(0, buf, sizeof buf);
        if (n==0){
            fprintf(2, "Wenqing says: finish!\n");
            exit(0);
        }
        if (n<0){
            fprintf(2, "read error\n");
            exit(1);
        }
        if (write(1, buf, n)!=n){
            fprintf(2, "write error\n");
            exit(1);
        }
    }
}
