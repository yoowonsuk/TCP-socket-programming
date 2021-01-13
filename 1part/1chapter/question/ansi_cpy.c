#include <stdio.h>
#include <stdlib.h>
//#include <fcntl.h>
//#include <unistd.h>
#include "error_handling.h"
#define BUF_SIZE 30

int main(void)
{
	FILE * src = fopen("src.txt", "rb");
	FILE * dst = fopen("dst.txt", "wb");

	char buf[BUF_SIZE];
	int readCnt;

	if(src == NULL || dst == NULL)
		error_handling("file open error");

	while(1)
	{
		readCnt = fread( (void*)buf, 1, BUF_SIZE, src);

		if(readCnt<BUF_SIZE)
		{
			if(feof(src) != 0)
				fwrite( (void*)buf, 1, readCnt, dst);
			else
				puts("file cpy error()");
			
			fclose(src);
			fclose(dst);
			break;
		}

		fwrite( (void*)buf, 1, BUF_SIZE, dst);
	}

	return 0;
}




