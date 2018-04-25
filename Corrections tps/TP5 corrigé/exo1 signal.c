#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/** 'signal' se comporte à la BSD style :
    une fois le handler appelé, il est réinitialisé à SIG_DFL
    il faut alors rappelé 'signal'
*/


void handler(int signum) {
    printf("I am immortal !!!\n");

}

int main(int argc, char **argv) {
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }
    if (signal(SIGTSTP, handler) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    while (1)
        /** 'usleep' renvoie une erreur lorsque SIGINT est emis : ne pas quitter si
         * sa valeur de retour est -1 */
        usleep(100000);

    return EXIT_SUCCESS;
}
