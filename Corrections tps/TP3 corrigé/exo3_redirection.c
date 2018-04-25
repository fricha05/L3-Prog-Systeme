#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
le dup sans le pipe sert à faire les redirections :
pour faire un ls > toto
*/

int main(int argc, char ** argv) {
    int fd;

    if (argc < 2) {
        printf("usage : %s fichier\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_WRONLY, 0)) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    dup2(fd, 1);

    if (close(fd) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    printf("redirection de la sortie standart dans %s\n", argv[1]);
    printf("dup2 pour la redirection de sortie\n");

    return EXIT_SUCCESS;
}



