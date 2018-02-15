#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void print(char* pathname){
	struct stat sm;
	if(lstat(pathname, &sm) == -1){
		perror("stat");
		exit(EXIT_FAILURE);
	}
	
	printf("Numéro d'inode : %ld\n", sm.st_ino);
	printf("Taille : %ld\n", sm.st_size);
	printf("Date de modification en secondes : %ld\n", sm.st_mtime);
	printf("Date de modification : %s", ctime(&sm.st_mtime));
	printf("Taille du fichier : %ld octets\n", sm.st_size);
	
	if(S_ISLNK(sm.st_mode)){
		printf("l\n");
		ssize_t size;
		char link_buf[BUFSIZ];
		if ((size = readlink(pathname, link_buf, BUFSIZ)) == -1) {
        perror("");
		exit(EXIT_FAILURE);
		}
		char * link_str = NULL;
		link_str = malloc(size + 1);
		if (NULL == link_str) {
			exit(EXIT_FAILURE);
		}

		snprintf(link_str, size + 1, "%s", link_str);
		printf(" -> %s\n", link_buf);

		free(link_str);
	}
	else if(S_ISREG(sm.st_mode)){
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
	if(argc != 2){
		printf("Erreurs dans les arguments\n");
		exit(EXIT_FAILURE);
	}
	print(argv[1]);
	exit(EXIT_SUCCESS);
}
