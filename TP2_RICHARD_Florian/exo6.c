#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>
#include <ftw.h>

#include "stat.h"
#include "display_files.h"

extern char * optarg;
extern int optind, opterr, optopt;

int main(int argc, char ** argv) {
    int r;
    int recur = 0;

    while((r = getopt(argc, argv, "R")) != -1)
        if (r == 'R')
            recur = 1;
    if (optind == argc) {
        if (display_dir_ftw(".", recur) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int i;
        for (i = optind; i < argc; ++i)
            if (display_ftw(argv[i], recur) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
    }
    exit(EXIT_SUCCESS);
}

