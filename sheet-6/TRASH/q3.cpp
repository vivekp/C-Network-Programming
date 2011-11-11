#include <iostream>
#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
	printf("Default send buffer size: ");
	printf(":");
	system("cat /proc/sys/net/core/wmem_default");
	printf("\n");
	printf("Default receive buffer size: ");
	system("cat /proc/sys/net/core/rmem_default");
	int t;
	printf("Input the new value for tcp receive buffer size: ");
	scanf("%d", &t);
	char str[100];
	sprintf(str, "echo %d > /proc/sys/net/core/wmem_default", t);
	system(str);
	printf("\n The new value has been set");
	
}
