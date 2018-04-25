#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZ 10


int main(int argc, char **argv) {
    int fd;
    int i;
    ssize_t r;
    char buf[BUFSIZ];

    if (argc < 2) {
        fprintf(stderr, "%s: missing file operand\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argc; ++i) {
        if ((fd = open(argv[i], O_RDONLY, 0)) == -1) {
            perror(argv[0]);
            return EXIT_FAILURE;
        }

        while ((r = read(fd, buf, BUF_SIZ)) != 0) {
            if (r == -1) {
                perror(argv[0]);
                return EXIT_FAILURE;
            }
            if (write(1, buf, r) == -1) {
                perror(argv[0]);
                return EXIT_FAILURE;
            }
        }

        if (close(fd) == -1) {
            perror(argv[0]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
