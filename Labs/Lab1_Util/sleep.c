#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

int
main(int argc, char* argv[])
{
    if (argc != 2)
    {
	fprintf(STDERR, "Wenqing says: Syntax error! Use: sleep <number>\n");
        exit(1);
    }
    int number = atoi(argv[1]);
    sleep(number);
    exit(0);
}
