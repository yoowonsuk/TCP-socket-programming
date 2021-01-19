#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char * argv[])
{	
	int sock;
	char message[BUF_SIZE];
	int str_len;

	socklen_t adr_sz;

	struct sockaddr_in serv_adr, from_adr;

	char msg1[] = "HI!";
	char msg2[] = "I'm another UDP host!";
	char msg3[] = "Nice to meet you";

	if(argc!=3)
		printf("Usage: %s <IP> <port>\n", argv[0]), exit(1);

	sock=socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	sendto(sock, msg3, sizeof(msg3), 0, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
