/* Author: Vivek Prakash
 * Date: Aug 1, 2011
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int main() {

	pid_t pid[7];
	int index = 0;

	printf("In the parent process\n");
	pid[0] = getpid();

	pid_t id;
	id = vfork();

	if(id < 0) 
		printf("Error: %d\n", errno);
	else if(id > 0) {
		/* In the parent process */
		pid[0] = getpid();
		pid_t id1 = vfork();
		if(id1 < 0) 
			printf("Error: %d\n", errno);
		else if(id1 > 0) {
			/* Back in the parent process */
		}
		else if (id1 == 0) {
			printf("In the child process - 2\n");
			pid[2] = getpid();
			
			pid_t id4;
			id4 = vfork();

			if(id4 < 0)
				printf("Error: %d\n", errno);
			else if(id4 > 0) {
				/* Back in the child process - 2 */
				pid_t id5;
				id5 = vfork();
				if(id5 < 0)
					printf("Error: %d\n", errno);
				else if(id5 > 0) {
					/* Back in the child process - 2 */
					pid_t id6;
					id6 = vfork();
					if(id6 < 0)
						printf("Error: %d\n", errno);
					else if(id6 > 0) {
						/* Back in the child process - 2 */
					} else if(id6 == 0) {
						printf("In the grand child process - 4\n");
						pid[6] = getpid();
						_exit(0);
					}
				}
				else if(id5 == 0) {
					printf("In the grand child process - 3\n");
					pid[5] = getpid();
					_exit(0);	
				}	
			}
			_exit(0);	
		}
		
		/* Print the pid array */
		for(int i = 0 ; i < 7 ; ++i)
			printf("%d\n", pid[i]);
	} else if(id == 0) {
		printf("In the child process - 1\n");
		pid[1] = getpid();

		pid_t id2;
		id2 = vfork();
		
		if(id2 < 0) 
			printf("Error: %d\n", errno);
		else if(id2 > 0) {
			/* Back in the child process - 1 */
			pid_t id3;
			id3 = vfork();
			if(id3 < 0) 	
				printf("Error: %d\n", errno);
			else if(id3 > 0) {
				/* Back in the child process - 1 */
			}
			else if(id3 == 0) {
				printf("In the grand child process - 2\n");
				pid[4] = getpid();
				_exit(0);
			}	
		}
		else if (id2 == 0) {
			printf("In the grand child process - 1\n");
			pid[3] = getpid();
			_exit(0);
		}	

		_exit(0);
	}
}
