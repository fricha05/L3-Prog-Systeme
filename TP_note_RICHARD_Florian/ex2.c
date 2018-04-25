#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char buff[BUFSIZ];
	int i;

	dup2(0,1);
	//redirection de l'entrée sur la sortie(n'affiche rien avec date | too save_date tutu ??)
	for(i = 1; i < argc; i++){
		if((fd = open(argv[i], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)) != -1){
			dup2(0, fd);
		}
		else{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}