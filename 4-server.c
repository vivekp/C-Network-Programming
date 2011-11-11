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

void usage();

int main(int argc, char **argv)
{
	if (argc < 2) {
		usage(argv[0]);
		exit(1);
	}

	struct sockaddr_in server, client;
	int sfd, port;

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		err(1, "Cannot create socket");
	
	port = atoi(argv[1]);
	bzero((char *)&server, sizeof(server));		 

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if ((bind(sfd, (struct sockaddr *)&server, sizeof(server))) < 0 )
		err(1, "Cannot bind to the socket");
	
	if (listen(sfd, 5) < 0) {
		if (errno = EADDRINUSE)
			err(1, "Another socket is already listening on the same port");
		else
			err(1, "Cannot listen on the socket");
	}

	printf("listening for connections on 127.0.0.1:%d\n", port);
	socklen_t clen;
	clen = sizeof(client);
	int cfd;
	if ((cfd = accept(sfd, (struct sockaddr *)&client, &clen)) < 0 )
		err(1, "Cannot accept connections on the socket");

	char buf[256];
	bzero(buf, 256);

	int n;
	if ((n = read(cfd, buf, 255)) < 0 )
		err(1, "Cannot read from the socket");
	
	printf("Message from client: %s\n", buf);
	
	char message[256];
	memmove(message, buf, 256);
	if ((n = write(cfd, message, 256)) < 0 )
		err(1, "Cannot write to the socket");

	close(sfd);	
	close(cfd);

	return 0;
}

void usage(char *prog)
{
	printf("usage: %s [port]\n", prog);
}
