#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * const argv[])
{
	printf("Bonjour\n");
	fork();
	printf("Au revoir\n");
	return 0;
}