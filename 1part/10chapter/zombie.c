#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if(!pid)
		puts("Hi, I am a child process");
	else
	{
		printf("Child Process ID: %d \n", pid);
		sleep(30);
	}

	if(!pid)
		puts("End Child Process");
	else
		puts("End parent process");

	return 0;
}
