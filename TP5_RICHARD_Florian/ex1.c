#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


void signal_handler(int signo){
	printf("\nI AM IMMORTAL!!\n");
}

int main(int argc, char const *argv[])
{
	while(1)
	{
		if(signal(SIGINT, signal_handler)==SIG_ERR){
			printf("Signal impossible\n");
		}
		// if(signal(SIGTSTP, signal_handler)==SIG_ERR){
		// 	printf("Signal impossible\n");
		// } Pour ^Z
		usleep(100000);
	}
	return EXIT_SUCCESS;
}