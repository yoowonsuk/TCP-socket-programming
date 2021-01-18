#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUF_SIZE 1024
void error_handling(char* message);
int calculate(int n, int opnds[], char op);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, recv_len = 0, result, times;

    SOCKADDR_IN serv_adr, clnt_adr;
    int clnt_adr_sz;

    if (argc != 2)
        printf("Usage : %s <port> \n", argv[0]), exit(1);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error!");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error!");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error!");

    clnt_adr_sz = sizeof(clnt_adr);

    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    if (clnt_sock == -1)
        error_handling("accept() error");
    else
        printf("Connected Client \n");

    // str_len = read(clnt_sock, message, BUF_SIZE); // assume 1byte
    // if(str_len == 1)

    times = 0;
    recv(clnt_sock, &times, 1, 0);

    while (recv_len < times * 4 + 1)
    {
        str_len = recv(clnt_sock, &message[recv_len], BUF_SIZE - 1, 0); // why not BUF_SIZE??
        recv_len += str_len;
    }

    result = calculate(times, (int*)message, message[recv_len - 1]);
    send(clnt_sock, (char*)&result, sizeof(result), 0); // sizeof(result) == 4
    closesocket(clnt_sock);
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

int calculate(int n, int opnds[], char op)
{
    int result = opnds[0], i;
    switch (op)
    {
    case '+':
        for (i = 1; i < n; i++)
            result += opnds[i];
        break;
    case '-':
        for (i = 1; i < n; i++)
            result -= opnds[i];
        break;
    case '*':
        for (i = 1; i < n; i++)
            result *= opnds[i];
        break;
    default:
        error_handling("invalid operator!");
    }
    return result;
}

