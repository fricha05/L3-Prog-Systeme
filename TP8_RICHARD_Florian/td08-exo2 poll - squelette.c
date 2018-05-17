#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define _BUFSIZ (32)

/**************************************************************************************
COURS SYLVAIN CHERRIER

poll/ppoll est une variante 'en mieux' de select/pselect

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
    - même valeur de retour que select
    - fds est un tableau de struct pollfd de taille nfds
    - timeout est une valeur en millisecondes (attente infinie si elle est négative)

la structure struct pollfd est la suivante:
    struct pollfd {
        int fd;         // Descripteur de fichier
        short events;   // Événements attendus
        short revents;  // Événements détectés
    };

    - events est un masque binaire dans lequel on indique ce qu'on attend
    - après l'appel, on teste les résultats dans revents

    les principales valeurs possibles pour events sont les suivantes:
        – POLLIN: attente en lecture (ou attente d'une connexion dans le cas d'une socket serveur)
        – POLLOUT: attente en écriture

    pour revents, on a aussi POLLUP et POLLRDHUP pour détecter une fin de connexion

**************************************************************************************/

int main(int argc, char **argv) {
     struct {
        char * msg;
        char * ms;
        int fildes[2]; // les tubes à écouter en parallèle
    } r[] = {
        { "salut\n", "500000" },
        { "bonjour\n", "250000" },
        { "ca va ?\n", "750000" },
        { NULL }
    };

    pid_t pid;
      // boucle de création des tubes et des fils
    // fermetures des extrémités du tube
    // recouvrement des fils par le processus de l'exo1
    /**
        ......
    */

    // pour les messages écrits par les fils et lus par le père
    char buf[_BUFSIZ];


    int nfds;
    /**
        ndfs = ....;
    */

    // Now, we use a poll selector to listen to all our children simultaneously
    struct pollfd fds[nfds];
    for (i = 0; i < nfds; ++i) {
        // affectation du desccrpteur
        // affectation évenement attendu
    }

    /** Waiting for something to be readable from one or many pipes.
	 * Note that with poll, there is no need to clear and set data
	 * before each call, as select requires */
	 /**
    while (....) {
        for (i = 0; ....; ++i) {
            // We read in each pipe that is marked as ready for a read operation
            if (....) { // masque sur revents
                ssize_t readsiz;
                readsiz = read(.................);
                write(......................);
            }
        }
    }
    */

    return EXIT_SUCCESS;
}
