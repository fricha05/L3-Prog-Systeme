#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void sig_handler(int signo){
	if(signo == SIGCHLD){
		printf("processus fils terminé\n");
	}
}

int main(int argc, char const *argv[]){
	if(signal(SIGCHLD, sig_handler) == SIG_ERR){
		printf("\nSignal impossible\n");
	}
	int i = 6;
	printf("i vaut %d et son adresse est %p\n", i, &i);
	switch(fork()){
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				i = 8;
				printf("i vaut %d et son adresse est %p\n", i, &i);
				exit(EXIT_SUCCESS);
			default:
				waitpid(-1, NULL, 0);
				i = 9;
				printf("i vaut %d et son adresse est %p\n", i, &i);
				
	}
	printf("i vaut %d\n", i);
	return 0;
}