#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void handler(int sig){
	if(sig == SIGUSR1){
		printf("cc ça marche\n");
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	char buf[BUFSIZ];
	int i;

	struct sigaction sigact ={};
	sigact.sa_handler = handler;
	sigemptyset(&(sigact.sa_mask));

	if(argc < 2){
		perror("pas d'argument");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < 5; i++){
		switch(pid = fork()){
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				pid = getpid();
				sprintf(buf,"%d\n", pid);
				write(1, buf, strlen(buf));
				while(sigaction(SIGUSR1, &sigact, NULL) != 0){
					pause();
				}
				exit(EXIT_SUCCESS);
		}
	}
	getchar();
	exit(EXIT_SUCCESS);
}