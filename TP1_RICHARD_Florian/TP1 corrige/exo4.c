#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stat.h"
#include "display_files.h"

int main(int argc, char ** argv) {
    /** aucun fichier passé au programme */
    if (argc <= 1) {
        fprintf(stderr, "%s: Unspecified file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat buf;
    time_t mtime;

    if (stat(argv[1], &buf) == -1) {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }

    mtime = buf.st_mtime;
    printf("%ld\n", mtime);

    /** test de modification du st_mtime */
    do {
        if (usleep(10000) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
        if (stat(argv[1], &buf) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
        printf("%ld\n", buf.st_mtime);
    } while(mtime == buf.st_mtime);
    printf("%s a été modifié à %ld\n", argv[1], buf.st_mtime);

    exit(EXIT_SUCCESS);
}
