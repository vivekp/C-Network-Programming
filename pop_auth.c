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


int main(int argc, char **argv)
{
	const int port = 110;
	const char *auth_host = "192.168.121.26";

	struct sockaddr_in server;
	struct hostent *host;
	int n, sfd;

	bzero((char *)&server, sizeof(server));

	if (inet_aton(auth_host, &server.sin_addr) == 0)
		err(1, "Not a valid auth host: %s\n", auth_host);
/*
	host = (struct hostent *) gethostbyaddr ((char *)&server.sin_addr.s_addr, sizeof (server.sin_addr.s_addr), AF_INET);	
	if(host == NULL)
		err(1, "%s: No such host", auth_host);
*/
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		err(1, "Cannot create socket");
	
	
	server.sin_family = AF_INET;
//	bcopy((char *)host->h_addr, (char *)&server.sin_addr.s_addr, host->h_length);
	server.sin_port = htons(port);

	if (connect(sfd, (struct sockaddr *)&server, sizeof(server)) < 0 )
		err(1, "Cannot connect to the socket");

	char buf[256];
	bzero(buf, 256);

	char input[256];
	char *key;

	/* Send User info */
	printf("\nUSER : ");
	key = "USER ";
	fgets(input, 255, stdin);
	strcat(buf, key);
	strcat(buf, input);

	printf("sending %s\n", buf); 
	if ((n = write(sfd, buf, strlen(buf))) < 0 )
		err(1, "Cannot write to the socket");

	/* Get first reply: connection is established */
	bzero(buf, 256);
	if ((n = read(sfd, buf, 255)) < 0 )
		err(1, "Cannot read from the socket");
	printf("Reply: %s\n", buf);

	/* Get second reply: valid mailbox */ 
	bzero(buf, 256);
	if ((n = read(sfd, buf, 255)) < 0 )
		err(1, "Cannot read from the socket");
	printf("Reply: %s\n", buf);

	/* Send Pass info */	
	printf("\nPASS: ");
	key = "PASS ";
	fgets(input, 255, stdin);
	strcat(buf, key);
	strcat(buf, input);

	printf("sending %s\n", buf); 
	if ((n = write(sfd, buf, strlen(buf))) < 0 )
		err(1, "Cannot write to the socket");

	/* Get third reply: password ok */ 
	bzero(buf, 256);
	if ((n = read(sfd, buf, 255)) < 0 )
		err(1, "Cannot read from the socket");
	printf("Reply: %s\n", buf);

	close(sfd);
	return 0;
}
