#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>



int main(int argc,char* argv[]) {
    int i ;
    int status ;
    int pid;

    for (i = 0; i < 20; i++) {
        switch (fork()) {
        case -1:
            perror("fork");
            exit(-1);
        case 0:
            usleep(i*100000) ;
            exit(i);
        default:
            break ;
        }
    }

    for (i = 0; i < 20; i++) {
        pid = waitpid(0, &status, 0) ;
        printf ("le fils de pid %d vient de se terminer ", pid) ;

        /** Ca n'etait pas demande, mais c'est bon a savoir */
        if (WIFEXITED(status))
            printf("normalement avec le code de retour %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("car il a recu le signal %d\n", WTERMSIG(status));
    }

    return EXIT_SUCCESS;
}
