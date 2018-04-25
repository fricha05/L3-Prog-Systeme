
/**
write n'est pas bufferisé, alors que printf l'est. L
c'est l'ordonnanceur qui décide qui s'exécute (et donc qui ne s'exécute pas).
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv) {
    char buf[38];
    pid_t pid = getpid();

    printf("mon PID est <%d>", pid);
    snprintf(buf, 18, "my PID is <%d>", pid);
    write(1, buf, 18);

    pid = fork();

    if (pid) { /** père */
        pid = getpid();
        printf("je suis le père et mon PID est <%d>", pid);
        snprintf(buf, 38, "I am the parent and my PID is <%d>", pid);
        write(1, buf, 38);
    } else { /** fils */
        pid = getpid();
        printf("je suis le fils et mon PID est <%d>", pid);
        snprintf(buf, 37, "I am the child and my PID is <%d>", pid);
        write(1, buf, 37);
    }

    puts("");

    return EXIT_SUCCESS;
}
