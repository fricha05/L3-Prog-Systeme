#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
le dup sans le pipe sert à faire les redirections :
pour faire un ls >toto
*/

int main(int argc, char ** argv) {
    int x;
    int i;
    int fd;

    if (argc < 2) {
        printf("usage : %s fichier\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY, 0)) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    dup2(fd, 0);

    if (close(fd) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 3; i++) {
        scanf("%d", &x);
        printf("j'ai lu %d\n", x);
    }

    return EXIT_SUCCESS;
}



