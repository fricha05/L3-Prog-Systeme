#include "ex1.h"

void myCat(int argc, char const *argv[]){
	char buf[BUFSIZ];
	int i = 1;
	int file;
	if(argc < 2){
		perror("Pas de fichier\n");
		exit(EXIT_FAILURE);
	}

	for(i = 1; i < argc; i++){
		file = open(argv[i], O_RDWR);
		if(file != -1){
			size_t size = read(file, buf, BUFSIZ);
			write(1, buf, size);
			write(1, "\n", 1);
		}
		else{
			perror("Pas un fichier");
			exit(EXIT_FAILURE);
		}
		close(file);
	}
}
