#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int n;

void handler(int sig){
	printf("%d o/s\n", n);
	n = 0;
	alarm(1);
}

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	struct sigaction sigact;
	int nb_octets_lus;

	sigact.sa_handler = handler;
	act.sa_handler = 0;
	sigemptyset(&(sigact.sa_mask));

	if(sigaction(SIGALRM, &sigact, NULL) == -1){
			perror("signal error");
			exit(EXIT_FAILURE);
	}
	alarm(1);

	while(1)
	{
		if((nb_octets_lus = read(0,buf,BUFSIZ))!=-1)
			n += nb_octets_lus;
	}
	exit(EXIT_SUCCESS);
}