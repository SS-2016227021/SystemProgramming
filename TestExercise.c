#include <stdio.h>
#include <unistd.h>

main()
{
	char *arglist[3];
	arglist[0] = "ls";
	arglist[1] = "demodir";
	arglist[2] = NULL;
	printf("About to exec ls demodir\n");
	execvp("ls", arglist);
	printf("ls is done. bye\n");
}
