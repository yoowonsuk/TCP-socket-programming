#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path, int flag); // file discriptor or -1


#include <unistd.h>
int close(int fd); // 0 or -1

#include <unistd.h>
ssizet write(int fd, const void * buf, size_t nbytes); // # of words delivered or -1

// (s)size_it -> sys/types.h

#include <unistd.h>
ssize_t read(int fd, void *buf, size_t nbytes); // # of words delivered or -1


