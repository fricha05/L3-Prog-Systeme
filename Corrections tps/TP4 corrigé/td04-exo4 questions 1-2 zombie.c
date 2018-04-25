#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFERSIZE 80

int main(int argc,char* argv[]) {
    int i;
    pid_t pid;
    char buffer[BUFFERSIZE];

    for (i = 0; i < 20; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(-1);
        }
        if (pid == 0) {
            snprintf(buffer, BUFFERSIZE, "je suis le numero %d, mon pid est %d et mon pere est %d\n",
                     i, getpid(), getppid() );
            write(1, buffer, strlen(buffer));
            exit(0);   /** A ne pas oublier pour eviter un nombre trop important de processus */
        }
    }

    while (1)
        pause();

    return EXIT_SUCCESS;
}
