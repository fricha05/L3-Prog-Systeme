/*
 * Exemples du cours de programmation système de Sébastien Paumier
 *
 * Copyright (C) 2010 Université Paris-Est Marne-la-Vallée <paumier@univ-mlv.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

#define N 5
#define SIZE 4096

int main(int argc,char* argv[]) {
int p[N][2];
for (int i=0;i<N;i++) {
	if (-1==pipe(p[i])) {
		perror("pipe");
		exit(1);
	}
	switch(fork()) {
	case -1: perror("fork"); exit(1);
	case 0: {
		/* Each son has to close the unused side of his own pipe */
		close(p[i][0]);
		/* It also has to close the copies of the descriptors
		 * corresponding to previously created children */
		for (int j=0;j<i;j++) {
			close(p[j][0]);
			close(p[j][1]);
		}
		/* Now we write messages to our father forever */
		srand(getpid());
		char tmp[128];
		while (1) {
			sprintf(tmp,"Child #%d: value=%d\n",i,rand()%100);
			write(p[i][1],tmp,strlen(tmp));
			usleep(rand()%10000000);
		}
	}
	default: {
		/* The father has nothing to do
		 *
		 * WARNING: DON'T DO close(p[i][1]) NOW !!!!!
		 *          If you do, you will induce pointer
		 *          errors on file descriptors made reusable
		 *          because of close. Well, after all, you should
		 *          try and see the mess it is :-)
		 */
	}
	}
}
/* All pipes have been created, we can safely close unused sides of them */
for (int i=0;i<N;i++) {
	close(p[i][1]);
}
/* Now, we use a poll selector to listen to all our children simultaneously */
struct pollfd tab[N];
for (int i=0;i<N;i++) {
	tab[i].fd=p[i][0];
	tab[i].events=POLLIN;
}
int n;
char tmp[SIZE];
while (1) {
	/* Waiting for something to be readable from one or many pipes.
	 * Note that with poll, there is no need to clear and set data
	 * before each call, as select requires */
	if (-1==(n=poll(tab,N,-1))) {
		perror("select");
		exit(1);
	}
	for (int i=0;i<N && n>0;i++) {
		/* We read in each pipe that is marked as ready for a read operation */
		if (tab[i].revents&POLLIN) {
			n--;
			int m=read(p[i][0],tmp,SIZE);
			write(1,tmp,m);
		}
	}
}
return 0;
}
