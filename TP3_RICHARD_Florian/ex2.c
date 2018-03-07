#include "ex2.h"

void myCp(int argc, char const *argv[]){
	char buf[BUFSIZ];
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
