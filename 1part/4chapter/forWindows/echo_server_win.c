#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    SOCKADDR_IN serv_adr, clnt_adr;
    int clnt_adr_sz;

    if (argc != 2)
        printf("Usage : %s <port> \n", argv[0]), exit(1);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == INVALID_SOCKET)
        error_handling("socket() error!");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (SOCKADDR*)&serv_adr, sizeof(serv_adr)) == SOCKET_ERROR)
        error_handling("bind() error!");

    if (listen(serv_sock, 5) == SOCKET_ERROR)
        error_handling("listen() error!");

    clnt_adr_sz = sizeof(clnt_adr);

    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_adr, &clnt_adr_sz);
        if (clnt_sock == INVALID_SOCKET)
            error_handling("accept() error");
        else
            printf("Connected Client %d \n", i + 1);

        while ((str_len = recv(clnt_sock, message, BUF_SIZE, 0)) != 0)
            send(clnt_sock, message, str_len, 0);

        closesocket(clnt_sock);
    }
    closesocket(serv_sock);
    WSACleanup();
    return 0;

}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

