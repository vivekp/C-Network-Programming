#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main()
{

    int retval;
    struct in_addr addrptr;
    memset(&addrptr, '\0', sizeof(addrptr));
    retval = inet_aton("192.168.121.156", &addrptr); 

    struct sockaddr_in dest;
    memset(&dest, '\0', sizeof(dest));
    dest.sin_addr.s_addr = inet_addr("192.168.121.156"); 
 

    char *ip;
    ip=inet_ntoa(dest.sin_addr);
    printf("IP Address is: %s\n",ip);
}
