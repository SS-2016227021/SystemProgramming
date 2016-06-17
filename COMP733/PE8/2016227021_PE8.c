#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define oops(m,x) { perror(m); exit(x); }

FILE *popen(const char *command, const char *mode){

        FILE *newfp;
        int pid, pp[2];

        if(pipe(pp) == -1)

				oops("pipe f", 1);

		if((pid = for()) == -1)

				oops("can't f", 2);

		if(strcmp(mode, "r") == 0){

				if(pid > 0){

					close(pp[1]);
					newfp = fdopen(p[0], "r");
					return newfp;

				}else if( pid == 0 ){

					close(pp[0]);

					if(dup2(pp[1], 1) == -1)
							oops("error", 3);

					close(pp[1]);
					execl("/bin/sh", "sh", "-c", command, NULL);

				}
		}
		if(strcmp(mode, "w") == 0){

			if(pid > 0){

				close(pp[0]);
				newfp = fdopen(p[1], "w");
				return newfp;

			}else if(pid == 0){

				close(pp[0]);
				newfp = fdopen(p[1], "w");
				return newfp;

			}else if(pid == 0){

				close(pp[1]);

				if(dup2(pp[0], 0) == -1)
					oops("error", 3);

				close(pp[0]);
				execl("/bin/sh", "sh", "-c", command, NULL);

			}
		}
}

int main(){
	FILE *newfp;
	char buf[BUFSIZ];
	newfp = popen("ls", "r");

	while(fgets(buf, BUFSIZ, newfp) != NULL)
			fputs(buf, stdout);
}
