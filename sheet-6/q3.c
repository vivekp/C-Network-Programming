#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>

int
main (int argc, char *argv[])
{

  int fd, val1, val2, len;

  printf("TCP:\n");  
  fd = socket (AF_INET, SOCK_STREAM, 0);
  getsockopt (fd, SOL_SOCKET, SO_RCVBUF, &val1, (socklen_t *) & len);
  getsockopt (fd, SOL_SOCKET, SO_SNDBUF, &val2, (socklen_t *) & len);
  printf ("Receive buffer : %d\n", val1);
  printf ("Send buffer : %d\n", val2);

  printf("\n");
  printf("UDP:\n");
  fd = socket (AF_INET, SOCK_DGRAM, 0);
  getsockopt (fd, SOL_SOCKET, SO_RCVBUF, &val1, (socklen_t *) & len);
  getsockopt (fd, SOL_SOCKET, SO_SNDBUF, &val2, (socklen_t *) & len);
  printf ("Receive buffer : %d\n", val1);
  printf ("Send buffer : %d\n", val2);

  printf("\n");

  fd = socket (AF_INET, SOCK_STREAM, 0);
  val1 = 2240;
  setsockopt (fd, SOL_SOCKET, SO_RCVBUF, &val1, sizeof(int));
  getsockopt (fd, SOL_SOCKET, SO_RCVBUF, &val1, (socklen_t *) & len);
  printf ("TCP:\nManual set: Receive buffer : %d\n", val1);

  return 0;
}
