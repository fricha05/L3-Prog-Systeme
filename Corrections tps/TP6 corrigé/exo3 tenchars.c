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
    unsigned char c;
    ssize_t readsiz = 0;

    while (read(pipefd, &c, 1) != -1) {
        readsiz++;
        if (readsiz <= 10) {
            c = toupper((int) c);
            write (1, &c, 1);
        } else
            close(pipefd);
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
