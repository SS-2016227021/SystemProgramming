#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int pid_counter = 1;

void handler(int sig){

	pid_t pid;

	int status;

	while((pid = waitpid(-1,&status,WNOHANG)) >0)

	printf("%d : Pid %d exited.\n",pid_counter++,pid);
	
}

int main(int argc, char* argv[]){

	signal(SIGCHLD,handler);

		int i, counter;

		if(argc!=2) return 0;

		counter = atoi(argv[1]);

		for(i=0;i<counter;i++)

			if(!fork()){

				printf("%d : Child pid is %d\n",i+1,getpid());
				sleep(5);
				exit(0);

			}

			printf("Parent pid is %d\n",getpid());

			getchar();

	return 0;
}

