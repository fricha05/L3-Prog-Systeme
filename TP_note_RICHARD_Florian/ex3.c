#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

char filetype(mode_t st_mode) {
    short i;
    struct _typemap {
        char type;
        short macro;
    } typemap[] = {
        {'f', S_ISREG(st_mode)},
        {'d', S_ISDIR(st_mode)},
        {'l', S_ISLNK(st_mode)} 
	};
	for (i = 0; i < 3; ++i)
        if (typemap[i].macro == 1)
            return typemap[i].type;
    return '?';
}

int main(int argc, char *argv[])
{
	struct stat buf;
	int fd;
	char str[BUFSIZ];
	if(argc < 2 || argc > 2){
		perror("necessite un seul argument");
		exit(EXIT_FAILURE);
	}

	if(stat(argv[1], &buf) == -1){
		perror(argv[0]);
        exit(EXIT_FAILURE);
	}

	if(filetype(buf.st_mode) == 'f'){
		printf("Nom :%s\nTaille : %d octets\n", argv[1], buf.st_size);
	}

	if(filetype(buf.st_mode) == 'd'){
		//scandir pour avoir la liste des fichiers triés par taille
		//mettre le premier fichier dans buf et print les infos
	}

	exit(EXIT_SUCCESS);
}