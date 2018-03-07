#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void myCp(int argc, char const *argv[]){
	char buf[BUFSIZ];
	int i = 1;
	int src, dest;
	if(argc < 2){
		perror("Pas de fichier\n");
		exit(EXIT_FAILURE);
	}
	src = open(argv[1], O_RDWR);
	dest = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if(dest == -1){
		perror("Pas de fichier destination\n");
		exit(EXIT_FAILURE);
	}

	if(src != -1){
		size_t size = read(src, buf, BUFSIZ);
		write(dest, buf, size);
	}
	else{
		perror("Pas un fichier");
		exit(EXIT_FAILURE);
	}
	close(src);
	close(dest);
}


int main(int argc, char const *argv[])
{
	myCp(argc, argv);
	exit(EXIT_SUCCESS);
}