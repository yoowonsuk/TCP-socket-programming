#include <sys/socket.h>

int socket(int domain, int type int protocol); //get(buy) telephone, file discriptor or -1
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen); // get number, 0 or -1
int listen(int sockfd, int backlog); // connect cable, 0 or -1
int accept(int sockfd, struct sockaddr *addr, socklet_t *addrlen); // ring up, file discriptor or -1


// make socket first
int connect(int sockfd, struct sockaddr *serv_addr, socklet_t addrlen); // 0 or -1
