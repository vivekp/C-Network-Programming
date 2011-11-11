#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned long long ulint;

ulint convert(char *);
ulint crc(ulint, ulint);

int main()
{
    ulint n, m;
    char *a = malloc(100);
    char *b = malloc(100);
    printf("Enter the message to be encoded: ");
    scanf("%s", a);
    printf("Enter the generator polynomial: ");
    scanf("%s", b);
    int len = strlen(b);
    int j;
    for (j = 1; j < len; j++)
	strcat(a, "0");
    n = convert(a);
    m = convert(b);
    ulint res = crc(n, m);
    printf("Remainder: ");
    int bl = 0;
    ulint i = 1;
    i = i << 63;
    while (i) {
	if (res & i)
	    bl = 1;
	if (bl) {
	    if (res & i)
		printf("1");
	    else
		printf("0");
	}
	i = i >> 1;
    }
    if (!bl)
	printf("0");
    printf("\n");
}

ulint crc(ulint a, ulint b)
{
    int alen = 0, blen = 0;
    int x = 1;
    int i = 1;
    for (i = 1; i <= 64; i++) {
	if (a & x)
	    alen = i;
	x *= 2;
    }
    x = 1;
    for (i = 1; i <= 64; i++) {
	if (b & x)
	    blen = i;
	x *= 2;
    }
    int cnt = alen - blen + 1;
    b = b << cnt - 1;
    alen--;
    while (cnt--) {
	if (a & 1 << alen)
	    a ^= b;
	b = b >> 1;
	alen--;
    }
    return a;
}

ulint convert(char *s)
{
    ulint x = 0;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; i++) {
	x = x << 1;
	if (s[i] == '1')
	    x += 1;
    }
    return x;
}
