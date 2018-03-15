#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * const argv[])
{
	pid_t child;
	switch(child = fork()){
		case -1:
			perror("erreur fork");
			exit(EXIT_FAILURE);
		case 0:
			execvp("ls", argv);
		default:
			//faire un wait
			printf("ls est terminé\n");
			exit(0);
	}
	// execvp("ls", argv);
	return 0;
}