#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

// slave <==> coroutine add sub mul
typedef struct {
    char *name;			        // nom de la coroutine
    int pipe_to_slave[2];   	// Premier tube : Père W [1] Fils R [0]
    int pipe_from_slave[2]; 	// Second tube  : Fils W [1] Père R [0]
    int pid;			        // pid du fils
} Slave;


int main (int argc,char* argv[]) {
    Slave slave =  { "./add" };

    // création du premier tube
    if ( pipe(slave.pipe_to_slave) == -1 ) {
        perror("pipe");
        exit(-1);
    }

    // création du second tube
    if ( pipe(slave.pipe_from_slave) == -1 ) {
        perror("pipe");
        exit(-1);
    }

    // Création du fils
    slave.pid = fork();
    if ( slave.pid == -1 ) {
        perror("fork");
        exit(-1);
    }
    // PROCESSUS PERE
    if ( slave.pid != 0 ) {
        printf ("fils %s crée de pid %d \n", slave.name, slave.pid) ;
    }
    // PROCESSUS FILS
    else {
        dup2(slave.pipe_to_slave[0],0);   // Fils R
        dup2(slave.pipe_from_slave[1],1); // Fils W
        execlp (slave.name, slave.name, NULL); // recouvrement du fils par le processus ./add
        perror("exec");
        exit(-1);
    }

    // PROCESSUS PERE
    while (1) {
        char cmd[20];
        char a[12];
        char b[12];

        // attention, pas de vérification des bornes
        // Père R sur l'entrée standard 0
        scanf("%s %s %s", cmd, a, b);

        if ( strcmp(slave.name, cmd) == 0 ) {
            char result[32];
            int read_size;
            char n = '\n';

            // Père W dans le premier tube : a \n b \n
            if ( write(slave.pipe_to_slave[1], a, strlen(a)) == -1 ) {
                perror("write");
                exit(-1);
            }
            if ( write(slave.pipe_to_slave[1], &n, 1) == -1 ) {
                perror("write");
                exit(-1);
            }
            if ( write(slave.pipe_to_slave[1], b, strlen(b)) == -1 ) {
                perror("write");
                exit(-1);
            }
            if ( write (slave.pipe_to_slave[1], &n, 1) == -1 ) {
                perror("write");
                exit(-1);
            }

            // Père R le résultat sur le second tube
            read_size = read(slave.pipe_from_slave[0], result, strlen(result));
            if ( read_size == -1 ) {
                perror("read");
                exit(-1);
            }

            // Père W le résultat sur la sortie standard 1
            if ( write(1, result, read_size) == -1 ) {
                perror("write");
                exit(-1);
            }
        } else {
            char * msg = "commande inconnue\n";
            write(1, msg, strlen(msg));
        }
    }

    return 0;
}
