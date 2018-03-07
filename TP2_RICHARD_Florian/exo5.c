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
    int recur = 0, mode = 0;
    int r;
	
	/*
	 * getopt récupère les options ajoutées par l'utilisateur et permet
	 * de définir ce qu'il faut afficher dans le listing des dossiers
	 */
	
    while((r = getopt(argc, argv, "nlR::")) != -1)
		switch(r){
			case 'R':
				recur = 1;
				break;
			case 'l':
				mode = 1;
				break;
			case 'n':
				mode = 2;
				break;
		}

    if (optind == argc) {
        if (display_dir_rec(".", recur, mode) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        int i;
        for (i = optind; i < argc; ++i)
            if (display_rec(argv[i], recur, mode) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
    }
     exit(EXIT_SUCCESS);
}
