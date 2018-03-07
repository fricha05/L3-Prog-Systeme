#include "ex3.h"

void redirect(int argc, char const *argv[]){
	int fd;
	
	if(argc < 2){
		perror("Pas de fichier\n");
		exit(EXIT_FAILURE);
	}
	
	fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);

	dup2(fd, STDOUT_FILENO);

	close(fd);
}
