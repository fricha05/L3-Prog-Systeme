#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

//printf bufferisé et pas write

#define MAX_COUNT 20

int main(int argc, char const *argv[])
{
	pid_t child, parent;
	char buf[BUFSIZ];
	int i, status;
	for (i = 1; i <= MAX_COUNT; ++i)
	{
		switch(child = fork()){
			case -1:
				perror("fork error");
				exit(EXIT_FAILURE);
			case 0:
				child = getpid();
				parent = getppid();
				sprintf(buf, "Mon numéro est %d, mon PID est %d et mon père est %d\n", i, child, parent);
				write(1, buf, strlen(buf));
				exit(EXIT_SUCCESS);
		}
		waitpid(-1, NULL, 0);
		printf("Le processus %d de PID %d vient de terminer\n", i, child);
	}
	/*
	les fils sont encore présent car si on n'utilise pas de waitpid(),
	les ressources utilisées pour les programmes ne sont pas libérées.
	waitpid() attend des changements d'état des processus et dans le cas 
	où un processus se termine, les ressources dédiées à se processus
	sont libérées.  
	*/
	for(;;){
		pause();
	}
	return 0;
}