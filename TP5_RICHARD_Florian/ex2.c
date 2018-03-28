#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>



void handler(int sig){
	printf("I AM IMMORTAL!!");
}

int main(int argc, char *argv[])
{
	struct sigaction sigact ={};
	sigact.sa_handler = handler;
	sigemptyset(&(sigact.sa_mask));

	while(1)
	{
		if(sigaction(SIGINT, &sigact, NULL) == -1){
			perror("signal error");
			exit(EXIT_FAILURE);
		}
		usleep(100000);
	}
	exit(EXIT_SUCCESS);
}