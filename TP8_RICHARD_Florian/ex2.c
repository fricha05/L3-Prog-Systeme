#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define _BUFSIZ (32)

int main(int argc, char **argv) {
     struct {
        char * msg;
        char * ms;
        int fildes[2]; // les tubes � �couter en parall�le
    } r[] = {
        { "salut\n", "500000" },
        { "bonjour\n", "250000" },
        { "ca va ?\n", "750000" },
        { NULL }
    };

    pid_t pid;

    // boucle de cr�ation des tubes et des fils
    // fermetures des extr�mit�s du tube
    // recouvrement des fils par le processus de l'exo1
    int tube[2];

    for(int i =0; i<N; i++){
        if(-1==tube[i])){
            perror("tube");
            exit(1);
        }
        switch(fork()){
            case -1:
                perror("fork");
                exit(1);
            case 0: {
                close(tube[1]);
            }
        }
    }

    // pour les messages �crits par les fils et lus par le p�re
    char buf[_BUFSIZ];

    // nfds correspond au num�ro du plus grand descripteur surveill� + 1 en LECTURE par le PERE
    int nfds;
    /**
        ndfs = ....;
    */

    // Now, we use a selector to listen to all our children simultaneously
    // fd_set d�signent des ensembles de descripteurs � surveiller:
    // readfds = en attente pour une lecture par le PERE
    fd_set readfds;

    // Waiting for something to be readable from one or many pipes
    // boucle pour les s�lecteurs et boucle imbriqu�e de gestion des E/S dans les tubes
    // la lecture dans le tube ne se fait que si le descripteur est pr�t
    // sinon le descripteur est activ�.
    /**
    while (......) {
        for (int i = 0; ....; ++i) {
            // We read in each pipe that is marked as ready for a read operation
            if (FD_ISSET(.............)) {
                ssize_t readsiz;
                readsiz = read(.................);
                write(......................);
            } else {
                // Clear and set the file descriptor set
                ....;
                .....;
            }
        }
    }
    */

    return EXIT_SUCCESS;
}
