#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

char *IPtoHOST(const char *IP)
{
	static char BUFFER[65] = "";

	struct sockaddr_in SIN;
	memset(&SIN, 0, sizeof(SIN));
	SIN.sin_family		= AF_INET;
	SIN.sin_addr.s_addr	= inet_addr(IP);
	SIN.sin_port		= 0;

	getnameinfo( (struct sockaddr *)&SIN, sizeof(SIN), BUFFER, 64, NULL, 0, 0);

	return BUFFER;
}

int main(int argc, char **argv)
{
	puts(IPtoHOST(argv[1])); 

    return 0;
}
