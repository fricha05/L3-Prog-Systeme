#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char *argv[])
{
	int fd = open("test", O_RDWR | O_CREAT);
	pid_t pid;

	if(pid = fork() <0){
		perror("fork failure");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0){
		if(fd == -1){
			perror("file error");
			exit(EXIT_FAILURE);
		}
		dup2(fd, 1);
		close(fd);
		execlp("ls", "ls");
	}
	waitpid(-1, NULL, 0);
	exit(EXIT_SUCCESS);
}