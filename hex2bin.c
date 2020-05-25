#include <stdlib.h>
#include <stdio.h>

void main(){
	char buffer[256];
	char out[256];
	printf("hex to bin\r\n");

	scanf("%s", &buffer);
	long b = strtoul(buffer, NULL, 16);
	_ltoa(b, out, 2);

	printf("%s\r\n", out);
}