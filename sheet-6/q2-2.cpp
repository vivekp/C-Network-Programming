#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include <err.h>

#define MAC_STRING_LENGTH 13

void getmac(char *iface)
{
  char *ret = (char *)malloc(MAC_STRING_LENGTH);
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

  strcpy(s.ifr_name, iface);
  if (fd >= 0 && ret && (ioctl(fd, SIOCGIFHWADDR, &s) == 0))
  {
    int i;
    for (i = 0; i < 6; ++i)
	  printf("%.2X", (unsigned char) s.ifr_addr.sa_data[i]);
  }
  printf("\n");
}

int main(int argc, char **argv)
{
  if(argc != 2)
	err(1, "usage: %s iface\n", argv[0]);
  getmac(argv[1]);
  return 0; 
}
