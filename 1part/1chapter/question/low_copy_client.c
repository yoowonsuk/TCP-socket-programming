#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	// socket
	int sock;
	struct sockaddr_in serv_addr;

	// file
	int fd;
	char message[BUF_SIZE];
	int str_len;

	fd = open("low_copy_data.txt", O_CREAT|O_WRONLY|O_TRUNC);
	if(fd == -1)
		error_handling("open() error!");

	if(argc != 3)
		printf("Usage : %s <IP> <port>\n", argv[0]), exit(1);

	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error!");

	while( str_len=read(sock, message, sizeof(message)-1) )
	{
		if(str_len==-1)
			error_handling("read() error!");
		
		else if(write(fd, message, sizeof(message)) == -1)
			error_handling("write() error!");
	}

	close(sock);
	close(fd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

	
