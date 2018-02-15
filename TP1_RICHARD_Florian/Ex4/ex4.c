#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

int main(int argc, const char* argv[]){
	if(argc < 1 || argc > 2){
		perror("wrong number of file in argument");
		exit(EXIT_FAILURE);
	}
	struct stat buf;
	if(stat(argv[1], &buf) != -1){
		double d = buf.st_mtime;
		while(1){
			sleep(1);
			stat(argv[1], &buf);
			if(buf.st_mtime != d){
				exit(EXIT_SUCCESS);
			}
		}
	}
	else{
		perror("arguments error");
		exit(EXIT_FAILURE);
	}
}
//Sur un répertoire, l'ajout ou la suppression d'un fichier ou dossier dans le répertoire le modifie.
//La modification d'éléments dans le répertoire ne le modifie pas.
