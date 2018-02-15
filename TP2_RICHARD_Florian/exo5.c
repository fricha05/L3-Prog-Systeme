#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>

#include "stat.h"
#include "display_files.h"

extern char * optarg;
extern int optind, opterr, optopt;

/*char opt_type(char** argv){
	int r;
	while((r = getopt(argc, argv, "nlR::")) != -1){
        short i;

        struct _optselect{
        	char opt;
        	char macro;
        }optselect[] ={
        	{'n', r}, 
        	{'l', r},
        	{'R', r}
        };
        for(i = 0; i < 3; i++){
        	if(optselect[i].macro == optselect[i].opt){
        		return optselect[i].opt;
        	}
        }
        return '0';
    }
}*/

int main(int argc, char ** argv) {
    int recur = 0;
    int r;

    while((r = getopt(argc, argv, "R")) != -1)
        if (r == 'R')
            recur = 1;

    if (optind == argc) {
        if (display_dir_rec(".", recur) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int i;
        for (i = optind; i < argc; ++i)
            if (display_rec(argv[i], recur) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
    }
     exit(EXIT_SUCCESS);
}
