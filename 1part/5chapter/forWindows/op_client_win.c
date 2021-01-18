#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET sock;
    int times, i, result;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    SOCKADDR_IN serv_adr;

    if (argc != 3)
        printf("Usage : %s <IP> <port>\n", argv[0]), exit(1);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error!");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected..........");

    puts("Operand count: ");
    times = (getchar() - (int)'0');
    message[0] = (char)times;

    for (i = 0; i < times; i++)
    {
        printf("Operand: %d: ", i + 1);
        scanf("%d", (int*)&message[i * 4 + 1]);
    }
    getchar();
    puts("Operator: ");
    message[times * 4 + 1] = getchar();
    send(sock, message, times * 4 + 2, 0);
    recv(sock, &result, 4, 0); // no guarantee 4 byte.. should implement for loop

    printf("Operation result: %d \n", result);
    closesocket(sock);
    WSACleanup();
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

