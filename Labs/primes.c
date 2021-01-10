#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define IN  0
#define OUT 1
#define ERR 2

#define READEND  0
#define WRITEEND 1

int 
main(){
    int numbers[36], p[2];
    int i, index = 0;
    int pid;
    for (i = 2; i <= 35; i++)
    {
        numbers[index] = i;
        index++;
    }
    while (index > 0)
    {
        pipe(p);
        if ((pid = fork()) < 0) 
        {
            fprintf(ERR, "fork error\n");
            exit(0);
        }
        else if (pid == 0) //child process
        {
            close(p[WRITEEND]);
            int prime = 0;
            int buf = 0;
            index = -1;
            
            while (read(p[READEND], &buf, sizeof(buf)) != 0) //keep reading from readend
            {
                // the first number must be prime
                if (index < 0) 
                {   prime = buf; 
                    index ++;
                }
                else
                {
                    if (buf % prime != 0) {
                            numbers[index] = buf;
                            index++;
                    }
                }
            }
            printf("prime %d\n", prime);
            // fork again until no prime
            close(p[READEND]);
        }
        else // parent process
        {
            close(p[READEND]);
            for (i = 0; i < index; i++)
            {
                write(p[WRITEEND], &numbers[i], sizeof(numbers[i]));
            }
            close(p[WRITEEND]);
            wait((int *)0);
            exit(0);
        }
    }
    exit(0);
}