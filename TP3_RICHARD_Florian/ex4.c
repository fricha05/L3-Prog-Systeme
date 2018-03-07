#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
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
	
	scanf("%s", str);
	printf("J'ai lu %s\n", str);

	close(fd);
	
	exit(EXIT_SUCCESS);
}