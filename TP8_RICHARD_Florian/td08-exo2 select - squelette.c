#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define _BUFSIZ (32)

/**************************************************************************************
COURS SYLVAIN CHERRIER

probl�me: on fait de l'attente active

solution: ne faire des E/S que quand on est s�r qu'elles ne bloqueront pas, gr�ce aux s�lecteurs

un s�lecteur permet de surveiller un ensemble de descripteurs:
    � bloque tant qu'il n'y a rien � faire
    � rend la main d�s qu'il y a au moins une op�ration possible sans bloquer


int select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

les fd_set d�signent des ensembles de descripteurs � surveiller:
    � readfds = en attente pour une lecture
    � writefds =en attente pour une �criture
    � exceptfds = en attente d'"�v�nements exceptionnels" (man select dixit)


on manipule les fd_set avec les fonctions suivantes:
    � void FD_CLR(int fd, fd_set *set);
    � int FD_ISSET(int fd,fd_set *set);
    � void FD_SET(int fd, fd_set *set);
    � void FD_ZERO(fd_set *set);
on cr�e donc des ensembles avec les descripteurs � surveiller (NULL  =ensemble vide)

nfds doit correspondre au num�ro du plus grand descripteur surveill� + 1

si timeout est non NULL, il d�finit un d�lai au bout duquel select retournera,
m�me en l'absence d'op�ration possible sur un des descripteurs surveill�s

avant chaque appel � select, on doit initialiser l'ensemble � surveiller

apr�s chaque appel, on teste chaque descripteur avec FD_ISSET

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
