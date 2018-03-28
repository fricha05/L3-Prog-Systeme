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
	int i = 6;
	// fork();
	printf("i vaut %d et son adresse est %p\n", i, &i);
	//après le fork, les adresses sont identiques.
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
	/*
	On remarque que les valeurs de i changent mais que son adresse
	reste la même. De plus, la valeur de i est celle attribué par
	le père qui modifie sa valeur après la fin du programme du fils.
	*/
	return 0;
}