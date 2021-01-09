#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define IN  0
#define OUT 1
#define ERR 2

#define READEND  0
#define WRITEEND 1

int readwritepipe(int p[2], int text){
// given a pipe, create the parent and child processes
// write a number stored in text from parent process to child process
    int pid;
    char buf[10];
    if ((pid = fork()) < 0)
    {
        fprintf(ERR, "fork error\n");
        exit(1);
    }
    else if (pid == 0) // child process
    {
        close(p[WRITEEND]);
        read(p[READEND], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        close(p[READEND]);
    }
    else // parent process
    {
        close(p[READEND]);
        write(p[WRITEEND], text, 4);
        close(p[WRITEEND]);
    }
    exit(0);
}

int main(){
    // initialize the pipeline
    int p[35][2];
    int i;
    for (i=0;i<35;i++){
        pipe(p[i]);
    }
    for (i=0;i<35;i++){
        readwritepipe(p[i], i);
    }
    exit(0);
}