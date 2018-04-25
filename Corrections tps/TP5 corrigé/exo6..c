#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "%s PROGRAM\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid) { /** père */
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
        if (!WEXITSTATUS(status))
            printf("OK\n");
        else
            printf("ERREUR\n");
    } else { /** fils */
        int null_fd;
        if ((null_fd = open("/dev/null", O_WRONLY)) == -1) {
            perror("open");
            return EXIT_FAILURE;
        }
        if ((dup2(null_fd, 1) || dup2(null_fd, 2)) == -1) {
            perror("dup2");
            return EXIT_FAILURE;
        }
        if (execvp(argv[1], &argv[1]) == -1) {
            perror("execvp");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
