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
    - m�me valeur de retour que select
    - fds est un tableau de struct pollfd de taille nfds
    - timeout est une valeur en millisecondes (attente infinie si elle est n�gative)

la structure struct pollfd est la suivante:
    struct pollfd {
        int fd;         // Descripteur de fichier
        short events;   // �v�nements attendus
        short revents;  // �v�nements d�tect�s
    };

    - events est un masque binaire dans lequel on indique ce qu'on attend
    - apr�s l'appel, on teste les r�sultats dans revents

    les principales valeurs possibles pour events sont les suivantes:
        � POLLIN: attente en lecture (ou attente d'une connexion dans le cas d'une socket serveur)
        � POLLOUT: attente en �criture

    pour revents, on a aussi POLLUP et POLLRDHUP pour d�tecter une fin de connexion

**************************************************************************************/

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
    /**
        ......
    */

    // pour les messages �crits par les fils et lus par le p�re
    char buf[_BUFSIZ];


    int nfds;
    /**
        ndfs = ....;
    */

    // Now, we use a poll selector to listen to all our children simultaneously
    struct pollfd fds[nfds];
    for (i = 0; i < nfds; ++i) {
        // affectation du desccrpteur
        // affectation �venement attendu
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
