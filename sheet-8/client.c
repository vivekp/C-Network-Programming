/* Author: Vivek Prakash
 * Date: Aug 1, 2011
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

void usage();

int main(int argc, char **argv)
{
	if (argc < 3) {
		usage(argv[0]);
		exit(1);
	}

	struct sockaddr_in server;
	struct hostent *host;
	int sfd, port;

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		err(1, "Cannot create socket");
	
	port = atoi(argv[2]);
	host = (struct hostent *)gethostbyname(argv[1]);
	if(host == NULL)
		err(1, "%s: No such host", argv[1]);

	bzero((char *)&server, sizeof(server));
	server.sin_family = AF_INET;
	bcopy((char *)host->h_addr, (char *)&server.sin_addr.s_addr, host->h_length);
	server.sin_port = htons(port);

	if (connect(sfd, (struct sockaddr *)&server, sizeof(server)) < 0 )
		err(1, "Cannot connect to the socket");

	char *term_buf = "stop";

	char buf[256];
	do {
		bzero(buf, 256);
		printf("\nPlease enter the string: ");
		fgets(buf, 255, stdin);
	
		int n;
		if ((n = write(sfd, buf, strlen(buf))) < 0 )
			err(1, "Cannot write to the socket");

		char msg[256];
		bzero(msg, 256);
		if ((n = read(sfd, msg, 255)) < 0 )
			err(1, "Cannot read from the socket");

		printf("Server replied this message: %s\n", msg);
	} while(strcmp(term_buf, buf)); 
	close(sfd);
	
	return 0;
}

void usage(char *prog)
{
	printf("usage: %s [hostname] [port]\n", prog);
	return;
}
