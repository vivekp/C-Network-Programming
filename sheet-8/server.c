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
#include <string.h>

void usage();
char *strrev(char *);

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

	char *term_buf = "stop";

	while(1) {
		char buf[256];
		bzero(buf, 256);

		int n;
		if ((n = read(cfd, buf, 255)) < 0 )
			err(1, "Cannot read from the socket");
		
		printf("String from client: %s\n", buf);

		int terminate = 0;
		if(!strcmp(term_buf, buf)) { 
			terminate = 1;	
			exit(0);
		}

		int flag = is_palindrome(buf);	
		char message[256];
		memmove(message, buf, 256);
		char *status = flag ? "\t is palindrome.\n" : "\t is not palindrome\n";
		strcat(message, status);
	
		if(terminate)
			strcpy(message, "Server exiting\n");
		if ((n = write(cfd, message, 256)) < 0 )
			err(1, "Cannot write to the socket");
		if(terminate)
			exit(0);
	}
	close(sfd);	
	close(cfd);

	return 0;
}

void usage(char *prog)
{
	printf("usage: %s [port]\n", prog);
}

int is_palindrome(char *s){
	int len = strlen(s);
	int i;
	for(i = 0 ; i < (len/2) ; ++i){
		if(s[i] != s[len-i-1]) return 0;
	}
	return 1;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
