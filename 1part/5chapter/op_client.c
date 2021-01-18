#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock, times, i, result;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;
	struct sockaddr_in serv_adr;

	if(argc != 3)
		printf("Usage : %s <IP> <port>\n", argv[0]), exit(1);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error!");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected..........");

	puts("Operand count: ");
	times = (getchar() - (int)'0');
	message[0] = (char)times;

	for(i=0; i<times; i++)
	{
		printf("Operand: %d: ", i+1);
		scanf("%d", (int*)&message[i*4 + 1]);
	}
	getchar();
	puts("Operator: ");
	message[times*4 + 1] = getchar();
	write(sock, message, times*4+2);
	read(sock, &result, 4); // no guarantee 4 byte.. should implement for loop
	
	printf("Operation result: %d \n", result);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
