#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * const argv[])
{
	pid_t child1;
	pid_t child2;
 	if(argv[1] == NULL){
		perror("Pas d'argument");
		exit(EXIT_FAILURE);
	}
	switch(child1=fork()){
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
		case 0:
			execvp(getenv("RUN_0"), argv);
		default:
			printf("\n");
	}
	switch(child2=fork()){
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
		case 0:
			execvp(getenv("RUN_1"), argv);
		default:
			printf("\n");
	}
	return 0;
}