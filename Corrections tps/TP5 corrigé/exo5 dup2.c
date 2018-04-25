#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv) {
    int fd;

    if (argc < 2) {
        fprintf(stderr, "%s OUTPUT\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((fd = open(argv[1],
                   O_CREAT | O_WRONLY | O_TRUNC,
                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    if (dup2(fd, 1) == -1) {
        perror("dup2");
        return EXIT_FAILURE;
    }

    if (execlp("ls", "ls", NULL) == -1) {
        perror("execlp");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
