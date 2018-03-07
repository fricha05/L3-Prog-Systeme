#include "ex4.h"

void redirect2(int argc, char const *argv[]){
	int fd;
	char str[BUFSIZ];
	
	if(argc < 2){
		perror("Pas de fichier\n");
		exit(EXIT_FAILURE);
	}
	
	fd = open(argv[1], O_RDONLY);

	if(fd == -1){
		perror("Le fichier n'existe pas\n");
		exit(EXIT_FAILURE);	
	}

	dup2(fd, STDIN_FILENO);
	
	fgets(str, BUFSIZ, stdin);
	printf("J'ai lu %s\n", str);

	close(fd);
}
