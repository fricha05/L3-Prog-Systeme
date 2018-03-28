#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	char buf[BUFSIZ];
	pid_t monpid = getpid();
	printf("mon PID est %d ", monpid);
	sprintf(buf, "my PID is %d ", monpid);
	write(1,buf, strlen(buf));
	switch(fork()){
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
		case 0:
			printf("je suis le fils et mon PID est %d", getpid());
			sprintf(buf, "I am the child process and my PID is %d ", getpid());
			write(1,buf, strlen(buf));
		default:
			waitpid(-1, NULL, 0);
			printf("je suis le père et mon PID est %d", getpid());
			sprintf(buf, "I am the parent process and my PID is %d ", getpid());
			write(1,buf, strlen(buf));
	}
	return 0;
}