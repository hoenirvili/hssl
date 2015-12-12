#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int a;
const char *c = "Aceasta este o minciuna";

int main(void) {
	size_t len = strlen(c);
	const char *save = c;

	for(size_t i=0; i<len; i++) {

		printf("%c", *c);
		c++;
	}
	printf("\n");

	printf("save = %s\n",save);

	printf("unsafe = %c\n",*c);

	if('\0' == *c) {
		printf("True");
	} else {
		printf("False");
	}
}

