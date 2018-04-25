#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int signum) {
    printf("I am immortal !!!\n");
}

int main(int argc, char **argv) {
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&(act.sa_mask));

    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }

    while (1)
        /** 'usleep' renvoie une erreur lorsque SIGINT est emis : ne pas quitter si
         * sa valeur de retour est -1 */
        usleep(100000);

    return EXIT_SUCCESS;
}
