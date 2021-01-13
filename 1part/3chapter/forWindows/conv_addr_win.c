#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE
#undef _UNICODE
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
    char* strAddr = "203.211.218.102:9190";

    char strAddrBuf[50];
    SOCKADDR_IN servAddr;
    int size;

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");

    size = sizeof(servAddr);
    WSAStringToAddress(strAddr, AF_INET, NULL, (SOCKADDR*)&servAddr, &size);

    size = sizeof(strAddrBuf);
    WSAAddressToString((SOCKADDR*)&servAddr, sizeof(servAddr), NULL, strAddrBuf, &size);

    printf("Second conv reult: %s \n", strAddrBuf);

    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
