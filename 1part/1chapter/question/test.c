#include <stdio.h>

int main(void)
{
	int a = 2;

	if(a > 0)
		if(a == 1)
			printf("a = 1");
		else
			printf("a positive, but not 1");

	return 0;
}
