#include "kernel/types.h"
#include "user/user.h"

void 
main(){
	int pid = fork();
	if(pid>0){
		printf("parent: child=%d\n", pid);
		pid = wait((int *) 0);
		printf("parent: child %d is done\n", pid); //the two processes: parent and child, may be excuted simutaneously
		//output may look like: parcehnitl: dc:h ielxdi=ti4ng
		exit(0);
	} else if(pid==0){
		printf("child: exiting\n");
		exit(0);
	} else {
		printf("fork error\n");
		exit(1);
	}
}
