#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

int main()
{
	int data[2], result[2];
	pipe(data);
	pipe(result);

	char *num;
	int nb = 256;
	num = (char *) malloc(nb);
	
	pid_t pid;
	if((pid = fork()) < 0)
		err(1, "Can not fork !");
	else if(pid > 0) {
		/* In the parent process */
		close(data[0]);
		char buf[256];
//		read(data, buf, 255);
	}
	else if(pid == 0) {
		/* In the child process */
		close(data[1]);

		int n;
		fscanf(stdin, "%d", &n);
		printf("%d\n", n);
		
		printf("Enter numbers: ");
		int nr = getline(&num, &nb, stdin);
		if(nr == -1) 
			err(1, "getline error");
		printf("%s\n", num);	

		_exit(0);
	}
	_exit(0);
}
