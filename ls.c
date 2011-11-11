#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <err.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid;
	if((pid = fork()) < 0)
		err(1, "Cannot fork!");
	else if(pid == 0) {
			char *lsarg[argc];
	
			int i;		
			for(i = 0 ; i < argc-1 ; ++i)
				lsarg[i] = strdup(argv[i+1]);

			lsarg[argc-1] = NULL;

			for(i = 0 ; i < argc-1 ; ++i)
				printf("%s ", lsarg[i]);
			printf("\n");		
		execv("/bin/ls", lsarg);	
		err(1, "Return not expected. Must be an execve error!");
	}
	else if(pid > 0) {
		wait(NULL);
	}
	return 0;	
}
