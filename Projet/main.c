#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "getopt.h"

int main(int argc, char *const argv[]) {

    if(argc != 5){
        perror("il faut 5 arguments");
        exit(EXIT_FAILURE);
    }

    options(argc, argv);
    exit(EXIT_SUCCESS);
}
