#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stat.h"
#include "display_files.h"

int main(int argc, char ** argv){
    if (argc < 2) {
        if (display_dir(".") == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int i;
        for (i = 1; i < argc; ++i) {
            if (display(argv[i]) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    exit(EXIT_SUCCESS);
}
