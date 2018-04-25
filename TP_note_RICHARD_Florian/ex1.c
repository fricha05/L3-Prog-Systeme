#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char c;
	int status;
	pid_t child;
	switch(child = fork()){
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			for(c = 'a'; c <= 'z'; c++){
				printf("%c\n", c);
			}
			exit(EXIT_SUCCESS);
		default:
			break;
	}
	switch(child = fork()){
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			for(c = 'A'; c <= 'Z'; c++){
				printf("%c\n", c);
			}
			exit(EXIT_SUCCESS);
		default:
			break;
	}
	child = waitpid(0, &status, 0);
	printf("fin\n");
	exit(EXIT_SUCCESS);
}