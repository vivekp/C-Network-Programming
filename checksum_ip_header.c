#include <stdio.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned short u16;
typedef unsigned long u32;

#define hlen ((32*5)/4)		/* header length in hexadecimal format. */

u16 itoh(char);
u16 ip_sum_calc(u16 ,u16 []);

int main()
{
    char ipheader[hlen + 1];
    printf("Enter the 20 bytes IP Header in Hex: ");
    scanf("%s", ipheader);

    ipheader[hlen] = '\0';

    u16 buf[20];

    int i, j = 0;
    for (i = 0; i < hlen; i += 2) {
	u16 c1, c2;
	c1 = itoh(ipheader[i]);
	c2 = itoh(ipheader[i+1]);

	buf[j++] = ((c1 << 4) & 0xF0) + (c2 & 0xF);
	printf("%.2x ", buf[j-1]);
    }

    printf("\n");

    u16 sum;
    sum = ip_sum_calc(20, buf);
    printf("\nchecksum: %x\n", sum);

    return 0;
}

u16 ip_sum_calc(u16 len_ip_header, u16 buf[])
{
    u16 word16;
    u32 sum = 0;
    u16 i;

    // make 16 bit words out of every two adjacent 8 bit words in the packet
    // and add them up
    for (i = 0; i < len_ip_header; i = i + 2) {
	if (i == 10) continue;
	word16 = ((buf[i] << 8) & 0xFF00) + (buf[i + 1] & 0xFF);
	sum = sum + (u32) word16;
        printf("%.4x + ", word16);
    }

    // take only 16 bits out of the 32 bit sum and add up the carries
    while (sum >> 16)
	sum = (sum & 0xFFFF) + (sum >> 16);

    // one's complement the result
    sum = ~sum;

    return ((u16) sum);
}

u16 itoh(char c)
{
	switch(c) {
		case '0':
			return 0x0;
			break;
		case '1':
			return 0x1;
			break;
		case '2':
			return 0x2;
			break;
		case '3':
			return 0x3;
			break;
		case '4':
			return 0x4;
			break;
		case '5':
			return 0x5;
			break;
		case '6':
			return 0x6;
			break;
		case '7':
			return 0x7;
			break;
		case '8':
			return 0x8;
			break;
		case '9':
			return 0x9;
			break;
		case 'A':
		case 'a':
			return 0xA;
			break; 
		case 'B':
		case 'b':
			return 0xB;
			break; 

		case 'C':
		case 'c':
			return 0xC;
			break; 
		case 'D':
		case 'd':
			return 0xD;
			break; 
		case 'E':
		case 'e':
			return 0xE;
			break; 
		case 'F':
		case 'f':
			return 0xF;
			break;
		default:
			err(1, "Bad Input: %c\n", c);
			exit(EXIT_FAILURE);
			break; 
	}
	return -1;
}
