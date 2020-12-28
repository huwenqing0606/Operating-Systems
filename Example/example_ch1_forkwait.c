#include "kernel/types.h"
#include "user/user.h"

int 
main(){
	int pid = fork();
	if(pid>0){
		//printf("parent: child=%d\n", pid);
		pid = wait((int *) 0);
		printf("parent: child %d is done\n", pid);
		exit(0);
	} else if(pid==0){
		printf("child: exiting\n");
		exit(0);
	} else {
		printf("fork error\n");
		exit(1);
	}
}
