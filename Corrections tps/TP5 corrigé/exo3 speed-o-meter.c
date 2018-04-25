#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int n;

void handler(int signum) {
    printf("%d o/s\n", n);
    n = 0;
    alarm(1);
}

/** A tester avec find / 2>/dev/null | ./speedometer */
int main(int argc, char **argv) {
    char buf[BUFSIZ];
    struct sigaction act;
    int r;

    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&(act.sa_mask));

    if (sigaction(SIGALRM, &act, NULL) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    alarm(1);

    while (1) {
        if ((r = read(0, buf, BUFSIZ)) != -1)
            n += r;
    }
    return EXIT_SUCCESS;
}
