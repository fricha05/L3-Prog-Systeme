#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAXSPEED 10

static int n;

void handler(int sig){
	printf("%d o/s\n", n);
	n = 0;
	alarm(1);
}


int main(int argc, char const * argv[])
{
	char buf[BUFSIZ];
	struct sigaction sigact;
	int nb_octets_lus;

	sigact.sa_handler = handler;
	sigemptyset(&(sigact.sa_mask));

	if(sigaction(SIGALRM, &sigact, NULL) == -1){
			perror("signal error");
			exit(EXIT_FAILURE);
	}
	alarm(1);

	while(1)
	{
		if((nb_octets_lus = read(0,buf,BUFSIZ))!=-1){
			n += nb_octets_lus;
			write(1, buf, MAXSPEED);
		}
	}
	exit(EXIT_SUCCESS);
}