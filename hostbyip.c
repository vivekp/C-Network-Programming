/* Author: Vivek Prakash
 * Date: Aug 3, 2011
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <err.h>
#include <signal.h>

#define HTML 1

int main(int argc, char **argv)
{
    if (HTML)
	printf("%s%c%c\n", "Content-Type: text/HTML;charset=iso-8859-1", 13, 10);


    const char *laptop_ip[10] = { "192.168.121.151", "192.168.121.152", "192.168.121.153",
	"192.168.121.155", "192.168.121.156",
	"192.168.121.158", "192.168.121.159",
	"192.168.121.160", "192.168.121.161"
    };

    signal(SIGCHLD, SIG_IGN);

    int i;
    for (i = 0; i < 10; ++i) {
	pid_t pid;
	pid = fork();
	if (pid == 0) {
	    const char *ip = laptop_ip[i];
	    struct hostent *host;
	    struct sockaddr_in server;

	    if (inet_aton(ip, &server.sin_addr) == 0)
		warn("Not a valid ip address: %s", ip);

	    host = (struct hostent *) gethostbyaddr((char *) &server.sin_addr.s_addr, sizeof(server.sin_addr.s_addr), AF_INET);
	    if (host == NULL) {
		if (HTML) {
		    printf("<font color='green'>%s: Available</font><br/>", ip);
		} else {
		    printf("%c[%d;%d;%dm%s: Available\n", 0x1B, 1, 32, 40, ip);
		    printf("%c[%dm", 0x1B, 0);
		}
	    } else {
		struct in_addr **ipaddrlist;
		ipaddrlist = (struct in_addr **) host->h_addr_list;
		int j;
		for (j = 0; ipaddrlist[j] != NULL; ++j) {
		    if (HTML) {
			printf("<font color='red'>%s: %s</font></br>", inet_ntoa(*ipaddrlist[j]), host->h_name);
		    } else {
			printf("%c[%d;%d;%dm%s: %s\n", 0x1B, 1, 31, 40, inet_ntoa(*ipaddrlist[j]), host->h_name);
			printf("%c[%dm", 0x1B, 0);
		    }
		}

		/* printf("h_name: %s\nh_addrtype: %d\nh_length: %d\nh_addr: %ld\n", host->h_name, host->h_addrtype, host->h_length, atol(host->h_addr));
		 */
	    }
	    exit(1);
	} else if (pid > 0) {
	    if (i == 9)
		return 0;
	}
    }
    return 0;
}
