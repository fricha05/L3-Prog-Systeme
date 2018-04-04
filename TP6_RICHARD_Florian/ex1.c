#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t child;
	char buf[BUFSIZ];

	if(argc < 3){
		perror("pas assez d'arguments");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1){
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}

	if((child = fork()) != -1){
		switch(child){
			case 0://more R !W
				dup2(pipefd[0], 0);
				close(pipefd[1]);
				execlp(argv[2], argv[2], NULL);
				exit(EXIT_SUCCESS);
			default://ls W !R
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				execlp(argv[1], argv[1], NULL);
		}
	}
	exit(EXIT_SUCCESS);
}