#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFFERSIZE 1024


static void traitement(int sig) {
    int status,pid;
    char buff[BUFFERSIZE];

    /** Ici, on DOIT faire une boucle pour capturer tous les processus fils terminés
    car comme ils s'arretent rapidement, certains ne sont pas detectés comme terminés.
    Le man indique que waitpid retourne 0 si on lui passe l'option WNOHANG
    et qu'il n'y a plus de processus, mais cela ne semble pas fonctionner
    sous Linux. */
    while ((pid = waitpid(-1, &status, WNOHANG)) != 0) {
        if(pid == -1) {
            if ( errno == ECHILD )
                return;
            perror("waitpid");
            exit(-1);
        }
        snprintf(buff,BUFFERSIZE,"Le processus %d vient de terminer\n",pid);
        write(1,buff,strlen(buff));
    }

    snprintf(buff,BUFFERSIZE,"waitpid a retourne zero\n");
    write(1,buff,strlen(buff));
}


int main(int argc,char* argv[]) {
    int i;
    int status;
    pid_t pid;
    char buff[BUFFERSIZE];

    signal(SIGCHLD,traitement);

    for (i = 0 ; i < 10 ; i++) {
        switch(pid = fork()) {
        case -1: {
            perror("fork");
            exit(-1);
        }
        case 0: {
            snprintf(buff,BUFFERSIZE,"Je suis le numero %d, mon PID est %d et mon pere est %d\n",i,getpid(),getppid());
            write(1,buff,strlen(buff));
            sleep(4);
            exit(i);
            break;
        }
        default:
            break;
        }
    }
    while(1) {
        sleep(1);
    }

    return EXIT_SUCCESS;
