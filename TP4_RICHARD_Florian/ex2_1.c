#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	printf("%s\n",getenv("RUN_0"));
	printf("%s\n",getenv("RUN_1"));
	printf("%s\n",getenv("RUN_2"));

	//parcourir les variables d'environnement ?

	return 0;
}