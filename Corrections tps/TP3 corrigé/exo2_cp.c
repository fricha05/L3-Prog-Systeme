#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZ 10


int main(int argc, char **argv) {
    int src, dst, r;
    char buf[BUF_SIZ];

    if (argc < 2) {
        fprintf(stderr, "%s: missing file operand\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc < 3) {
        fprintf(stderr, "%s: missing destination file operand after `%s'\n",
                argv[0], argv[1]);
        return EXIT_FAILURE;
    }

    if ((src = open(argv[1], O_RDONLY, 0)) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    /** Attention au champ mode pour les droits, sinon, ils sont positionnés de manière aléatoire */
    if ((dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    while ((r = read(src, buf, BUF_SIZ)) != 0) {
        if (r == -1) {
            perror(argv[0]);
            return EXIT_FAILURE;
        }
        if (write(dst, buf, r) == -1) {
            perror(argv[0]);
            return EXIT_FAILURE;
        }
    }

    if ((close(src) == -1) || (close(dst) == -1)) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
