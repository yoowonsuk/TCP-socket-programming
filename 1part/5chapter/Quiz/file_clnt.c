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
	int sock;
	char message[BUF_SIZE];
	int str_len, i;
	struct sockaddr_in serv_adr;
	FILE * fp; // int
	char file_name[BUF_SIZE];

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

	fputs("Input file name: ", stdin);
	//fgets(file_name, sizeof(file_name), stdin);
	scanf("%s", file_name);
	fp = fopen(file_name, "wb");
	// if(fp == NULL)

	write(sock, file_name, strlen(file_name)+1);
	while((str_len = read(sock, message, BUF_SIZE)) != 0)
		fwrite((void*)message, 1, str_len, fp);

	fclose(fp);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
