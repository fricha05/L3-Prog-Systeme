#include <ctype.h>
#include <unistd.h>


int parent(int pipefd) {
    size_t bufsiz = 16;
    char buf[bufsiz];
    ssize_t readsiz;
    while ((readsiz = read(0, buf, bufsiz)) != -1) {
        write (pipefd, buf, readsiz);
    }

    return 0;
}

int child(int pipefd) {
    size_t bufsiz = 16;
    unsigned char buf[bufsiz];
    ssize_t readsiz;
    unsigned int i;

    while ((readsiz = read(pipefd, buf, bufsiz)) != -1) {
        for (i = 0U; i < readsiz; ++i)
            buf[i] = toupper((int) buf[i]);
        write (1, buf, readsiz);
    }

    return 0;
}

int main(int argc, char **argv) {
    pid_t pid;
    int pipefd[2];

    pipe(pipefd);
    pid = fork();
    if (pid) {
        close(pipefd[0]);
        parent(pipefd[1]);
    } else {
        close(pipefd[1]);
        child(pipefd[0]);
    }

    return 0;
}
