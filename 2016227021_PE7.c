nclude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int newfd1[2];
	int newfd2[2];
	pid_t pid1;
	pid_t pid2;
	pid_t pid3;

	if(argc != 4) return -1;

		pid3= fork();

	if(pid3 == -1) return -1;

		else if(pid3 == 0){

		pipe(newfd1);
		pid1= fork();

		if(pid1 == -1) return -1;
			else if(pid1 == 0)
			{
			close(newfd1[1]);
			dup2(newfd1[0],0);
			pipe(newfd2);
			pid2 = fork();

			if(pid2 == -1) return -1;
				else if(pid2 == 0)
				{			
				close(newfd2[1]);
				close(0);
				dup2(newfd2[0],0);
				execlp(argv[3], argv[3], NULL);
			}else{
				close(newfd2[0]);
				close(1);
				dup2(newfd2[1], 1);
				execlp(argv[2], argv[2], NULL);
				exit(1);
			}
		}else{		
			close(newfd1[0]);
			dup2(newfd1[1],1);
			execlp(argv[1],argv[1],NULL);	
			exit(1);
		}	
	}else{
		;
	}

	return 0;

}

