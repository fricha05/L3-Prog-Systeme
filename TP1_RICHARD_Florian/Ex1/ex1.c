#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void print(char* pathname){
	struct stat sm;
	if(stat(pathname, &sm) == -1){
		perror("stat");
		exit(EXIT_FAILURE);
	}
	
	printf("Numéro d'inode : %ld\n", sm.st_ino);
	printf("Taille : %ld\n", sm.st_size);
	printf("Date de modification en secondes : %ld\n", sm.st_mtime);
	printf("Date de modification : %s", ctime(&sm.st_mtime));
	printf("Taille du fichier : %ld octets\n", sm.st_size);
	
	if(S_ISREG(sm.st_mode)){
		printf("f\n");
	}
	else if(S_ISDIR(sm.st_mode)){
		printf("d\n");
	}
	else{
		print("?\n");
	}
	exit(EXIT_SUCCESS);
}


int main(int argc, char** argv){
	if(argc > 1){
		print(argv[1]);
		exit(EXIT_SUCCESS);
	}
	printf("Pas de fichier en argument");
	exit(EXIT_FAILURE);
}
