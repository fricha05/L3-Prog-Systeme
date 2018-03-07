#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*Prend en argument le fichier dont il faut compter le nombre de mots*/
int wordCount(FILE* file);

/*Prend en argument le fichier dont il faut compter le nombre de lignes*/
int lineCount(FILE* file);

/*Prend en argument le fichier dont il faut compter le combre d'octets*/
int byteCount(FILE* file);

void myWc(int argc, char *argv[]);
