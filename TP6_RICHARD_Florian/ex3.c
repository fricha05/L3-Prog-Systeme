#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	int i = 0;
	pid_t child;
	char buf[BUFSIZ];

	if(pipe(pipefd) == -1){
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}

	if((child = fork()) != -1){
		switch(child){
			case 0:
				close(pipefd[1]);
				read(pipefd[0], buf, BUFSIZ);
				while(buf[i]){
					if(i<9){
						buf[i] = toupper(buf[i]);
						i++;
					}
					else{
						exit(EXIT_SUCCESS);
					}
				}
				write(0, buf, strlen(buf));
				exit(EXIT_SUCCESS);
			default:
				close(pipefd[0]);
				dup2(pipefd[1],1);
				scanf("%s", buf);
				write(pipefd[1], buf, strlen(buf));
		}
	}
	else{
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}