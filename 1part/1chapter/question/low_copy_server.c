#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define BUF_SIZE 100
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	// socket
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	// file
	int fd;
	char buf[BUF_SIZE];
	int valid;

	fd=open("data.txt", O_RDONLY);
	if(fd == -1)
		error_handling("open() error!");

	if(argc!=2)
		printf("Usage : %s <port>\n", argv[0]), exit(1);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");

	while(valid = read(fd, buf, sizeof(buf)))
	{
		if(valid == -1)
			error_handling("read() error!");
		write(clnt_sock, buf, sizeof(buf)); // sizeof(buf) can be changed into valid
	}

	close(clnt_sock);
	close(serv_sock);
	close(fd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

