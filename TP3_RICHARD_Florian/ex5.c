#include "ex5.h"

int wordCount(FILE* file){
	char buf[BUFSIZ];
	int word = 0;
	
	while(fscanf(file, "%s", buf) == 1){
		word++;
	}
	rewind(file);
	return word;
}

int lineCount(FILE* file){
	char buf[BUFSIZ];
	int line = 0;
	
	while(fgets(buf, sizeof(buf), file)){
		line++;
	}
	rewind(file);
	return line;
}

int byteCount(FILE* file){
	int bytes = 0;
	
	while (fgetc(file) != EOF){
		bytes++;
	}
	rewind(file);
	return bytes;
}

void myWc(int argc, char *argv[]){
	FILE* file;
	int o;
	if(argc < 2){
		perror("Pas de fichier\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if(file != NULL){
		while(optind < argc){
			if((o = getopt(argc, argv, "clw::")) != -1){
				switch(o){
					case 'w':
						printf("Nombre de mots : %d\n", wordCount(file));
						break;
					case 'l':
						printf("Nombre de lignes : %d\n", lineCount(file));
						break;
					case 'c':
						printf("Nombre d'octets : %d\n", byteCount(file));
						break;
				}
			}
			else{
				printf("Nombre de mots : %d\n", wordCount(file));
				printf("Nombre de lignes : %d\n", lineCount(file));
				printf("Nombre d'octets : %d\n", byteCount(file));
				optind++;
			}
		}
	}
	else{
		perror("Pas un fichier");
		exit(EXIT_FAILURE);
	}
    fclose(file);
}
