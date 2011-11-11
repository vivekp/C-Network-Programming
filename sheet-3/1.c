/* Author: Vivek Prakash
 * Date: Aug 1, 2011
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>

static void signal_usr_child(int);
static void signal_usr_grandchild(int);

void print_pid(int);

extern int errno;
int flag_child = 0;
int flag_child1 = 0;
int flag_child2 = 0;
int flag_grandchild = 0;

int main() {
	printf("In the parent process\n");
	print_pid(getpid());

	pid_t pid1, pid2;
	int status1, status2;

	if(signal(SIGUSR2, signal_usr_grandchild) == SIG_ERR)
		err(1, "Can not catch SIGUSR1\n");
	if(signal(SIGUSR1, signal_usr_child) == SIG_ERR)
		err(1, "Can not catch SIGUSR1\n");

	if((pid1 = fork()) < 0) 
		printf("Error: %d\n", errno);
	else if(pid1 > 0) {
		/* In the parent process */
		kill(pid1, SIGUSR1);	//send signal to child 1

		if((pid2 = fork())< 0)
			printf("Error: %d\n", errno);
		else if(pid2 > 0) {
			/* In the parent process */
			kill(pid2, SIGUSR1);	//send singal to child 2
		}
		else if(pid2 == 0) {
			printf("In the child process 2\n");
			/* In the child process */
			while(!flag_child);
			print_pid(getpid());

			pid_t pid3, pid4;
			if((pid3 = fork())< 0)
				printf("Error: %d\n", errno);
			else if(pid3 > 0) {
				/* In the child process 2 */
				kill(pid3, SIGUSR2);	//send singal to grand child 1 
			
				if((pid4 = fork()) < 0)
					printf("Error: %d\n", errno);
				else if(pid4 > 0) {
					kill(pid4, SIGUSR2);	//send signal to grand child 2
				}
				else if(pid4 == 0) {
					printf("In the grand child process 2\n");
					while(!flag_grandchild);
					print_pid(getpid());
					_exit(0);
				}
			}
			else if(pid3 == 0) {
				printf("In the grand child process 1\n");
				while(!flag_grandchild);
				print_pid(getpid());
				_exit(0);
			}
		_exit(0);
		}
	}
	else if(pid1 == 0) {
		printf("In the child process 1\n");

		while(!flag_child);
		print_pid(getpid());

		pid_t pid5, pid6;
		if((pid5 = fork())< 0)
			printf("Error: %d\n", errno);
		else if(pid5 > 0) {
			/* In the child process 2 */
			kill(pid5, SIGUSR2);	//send singal to grand child 3 
		
			if((pid6 = fork()) < 0)
				printf("Error: %d\n", errno);
			else if(pid6 > 0) {
				kill(pid6, SIGUSR2);	//send signal to grand child 4 
			}
			else if(pid6 == 0) {
				printf("In the grand child process 4\n");
				while(!flag_grandchild);
				print_pid(getpid());
				_exit(0);
			}
		}
		else if(pid5 == 0) {
			printf("In the grand child process 3\n");
			while(!flag_grandchild);
			print_pid(getpid());
			_exit(0);
		}

		_exit(0);
	}

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	_exit(0);
}

static void signal_usr_child(int signo)
{
/*	printf("Handling signal\n");
	if(signo == SIGUSR1)
		printf("Received SIGUSR1\n");
	else if(signo == SIGUSR2)
		printf("Received SIGUSR2\n");
*/
	flag_child = 1;
}

static void signal_usr_grandchild(int signo)
{
	flag_grandchild = 1;
}

void print_pid(int pid)
{
	printf("Process id: %d\n", pid);
}	
