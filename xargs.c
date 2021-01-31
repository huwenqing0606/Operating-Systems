#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define IN  0
#define OUT 1
#define ERR 2
#define MAXLINE 1024

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    char* params[MAXARG];
    int n, args_index = 0;
    int i;

    // argv[1] is the command cmd to be executed
    // argv[1],...,argv[argc-1] are the parameters in the original command
    // the first parameter is still argv[1], since for exec it is the name of the command
    char* cmd = argv[1];
    for (i = 1; i < argc; i++) params[args_index++] = argv[i];

    while ((n = read(IN, line, MAXLINE)) > 0) 
    // n is the number of bytes read from input and saved to line
    // read until the end of the IN file
    // append each argument to the original cmd and params
    {
        if (fork() == 0) // child process
        {
            char *arg = (char*) malloc(sizeof(line));
            int index = 0;
            for (i = 0; i < n; i++)
            {
                if (line[i] == ' ' || line[i] == '\n') // until a new param or command starts
                {
                    arg[index] = 0; // end of arg
                    params[args_index++] = arg; // save the current arg to params
                    index = 0; // reset arg index
                    arg = (char*) malloc(sizeof(line));
                }
                else arg[index++] = line[i]; // read each character in line and save to arg
            }
            arg[index] = 0;
            params[args_index] = 0;
            exec(cmd, params); // execute cmd with params in the current line
        }
        else wait((int*)0); // parent process
    }
    exit(0);
}