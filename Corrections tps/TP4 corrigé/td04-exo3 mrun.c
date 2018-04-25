#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char **argv) {
    unsigned int i = 1U;
    char key[16] = "RUN_0";
    char *value;
    pid_t pid;

    while ((value = getenv(key)) != NULL) {
        pid = fork();
        if (pid) { /** père */
            wait(NULL);
            snprintf(key, 16, "RUN_%d", i++);
        } else { /** fils */
            execvp(value, argv);
        }
    }

    return EXIT_SUCCESS;
}
