#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int FD01, FD02, OFFset, ren;
	char buffer[BUFSIZ];
	char filename[BUFSIZ];		

		if(argc != 3)
		{
			printf("usage : ./2016227021_PE3 file1 file2(or dir1)\n");

			return -1;
		}

		if(strcmp(argv[1],argv[2])==0)
		{
			printf("%s and %s are the same file\n",argv[1],argv[2]);

			return -1;
		}

		if((FD01 = open(argv[1], O_RDONLY))==-1)
		{
			perror(argv[1]);

			return -1;
		}

		if(TheDir(".",argv[2]) == 1)
		{
			printf("move file %s to directory %s\n",argv[1],argv[2]);				
			sprintf(filename,"%s/%s",argv[2],argv[1]);
			if((FD02 = creat(filename, 0644)) == -1){
				perror(filename);

				return -1;
			}
			else
			{ 
				while((OFFset = read(FD01, buffer, BUFSIZ))>0)
				{
					write(FD02, buffer, BUFSIZ);
				}
				unlink(argv[1]);
			}	
		}
		else
		{		
			printf("rename file %s to %s\n",argv[1],argv[2]);
			ren = rename(argv[1],argv[2]);		
		}

	close(FD01);
	close(FD02);

	return 0;	
}

int TheDir(char* cwd, char* dirname){
	DIR 			*dir_ptr;
	struct dirent	*direntp;

		if((dir_ptr = opendir(cwd)) != NULL)
		{
			while((direntp = readdir(dir_ptr)) != NULL)
			{
				if(direntp -> d_type == DT_DIR && strcmp(direntp -> d_name, dirname) == 0)

					return 1;
			}
		}

	return 0;
}
