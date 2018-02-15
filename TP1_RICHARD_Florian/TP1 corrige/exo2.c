#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stat.h"

int main(int argc, char ** argv) {
    if (argc > 1) {
        struct stat buf;

        if (lstat(argv[1], &buf) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }

        char type = filetype(buf.st_mode);
        affiche_infos(&buf, type, argv[1]);

        if (is_link(type)) {
            affiche_link(argv[1]);
        }
        printf("\n");
    }
    exit(EXIT_SUCCESS);
}
