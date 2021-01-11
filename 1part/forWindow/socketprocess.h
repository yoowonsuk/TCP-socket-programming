#include <winSock2.h>

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData); // 0 or error code

int main(int argc, char* argv[])
{
	WSADATA wsaData;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
		
	return 0;
}


int WSACleanup(void); // 0 or SOCKETERROR




SOCKET socket(int af, int type, int protocol); // socket handle or INVALID_SOCKET

int bind(SOCKET s, const struct sockaddr * name, int namelen); // 0 or SOCKET_ERROR

int listen(SOCKET s, int backlog); // 0 or SOCKET_ERROR

SOCKET accept(SOCKET s, struct sockaddr * addr, int * addrlen); // socket handle or INVALID_SOCKET



int connect(SOCKET s, const struct sockaddr * name, int namelen); //0 or SOCKET_ERROR



int closesocket(SOCKET s); // 0 or SOCKET_ERROR
