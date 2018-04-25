#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int n = 0;
static char *buf;


void handler(int signum) {
    if (write(1, buf, n) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    n = 0;
    alarm(1);
}

int main(int argc, char **argv) {
    struct sigaction act;
    long int bufsiz;
    int r;

    if (argc < 2) {
        fprintf(stderr, "%s: You must specify an integer\n", argv[0]);
        return EXIT_FAILURE;
    }

    bufsiz = strtol(argv[1], NULL, 10);
    if (errno != 0) {
        perror(argv[0]);
        return EXIT_SUCCESS;
    }

    buf = (char*) malloc(bufsiz);
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&(act.sa_mask));

    if (sigaction(SIGALRM, &act, NULL) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    alarm(1);

    while (1) {
        while (n < bufsiz) {
            if ((r = read(0, &(buf[n]), bufsiz - n)) != -1)
                n += r;
        }
    }

    return EXIT_SUCCESS;
}
