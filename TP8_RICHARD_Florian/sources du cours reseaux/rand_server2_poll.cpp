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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>

#define MAX_CONNECTIONS 16
#define BUFFER_SIZE 32

/**
 * This function takes a string representing the client request.
 * It deals with it, writing random characters to the client.
 *
 * Returns the number of numbers sent by the client. 0 means
 * that the connection should be closed.
 *
 * Examples:
 * 	"  23  14 "   => returns 2
 * 	"  23  14 . " => returns 0, because of the dot that cannot be read as a number
 */
int send_random_data(const char* buffer,int fd) {
    int pos=0;
    int n_numbers=0;
    unsigned int n,x;
    while (buffer[pos]!='\0') {
        int ret=sscanf(buffer+pos,"%u%n",&n,&x);
        pos=pos+x;
        if (ret==-1) return n_numbers;
        if (ret==0) return 0;
        n_numbers++;
        for (unsigned int i=0; i<n; i++) {
            char c='A'+rand()%26;
            write(fd,&c,1);
        }
    }
    return n_numbers;
}


void disconnect(int fd,int* tab) {
    printf("Client disconnection\n");
    close(fd);
    for (int i=0; i<MAX_CONNECTIONS; i++) {
        if (tab[i]==fd) {
            tab[i]=-1;
            break;
        }
    }
}


/**
 * This program is a server that listens for numbers as ASCII strings and
 * that returns as many random characters in A-Z as required.
 *
 * This version supports multiple connections with a single thread,
 * using poll selection.
 */
int main(int argc,char* argv[]) {
    if (argc!=2) {
        fprintf(stderr,"Usage: %s <port>\n",argv[0]);
        exit(1);
    }
    char foo;
    int PORT;
    if (1!=sscanf(argv[1],"%d%c",&PORT,&foo) || PORT<0 || PORT>=0x10000) {
        fprintf(stderr,"Invalid port number\n");
        exit(1);
    }

    int my_socket=socket(AF_INET,SOCK_STREAM,0);
    if (-1==my_socket) {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    /* We set up the port, using htons in ordre to respect the endianness
     * of the network protocol */
    addr.sin_port=htons(PORT);
    /* We bind the socket */
    if (-1==bind(my_socket,(const struct sockaddr*)(&addr),sizeof(addr))) {
        perror("bind");
        exit(1);
    }
    /* And we start listening for incoming connections,
     * allowing up to 16 simultaneous connections requests */
    if (-1==listen(my_socket,MAX_CONNECTIONS)) {
        perror("listen");
        exit(1);
    }
    /* We need an array to stock all descriptors being used
     * by client connections */
    int fds[MAX_CONNECTIONS];
    for (int i=0; i<MAX_CONNECTIONS; i++) {
        fds[i]=-1;
    }
    /* And we need another array to stock all informations needed
     * by poll */
    struct pollfd tab[MAX_CONNECTIONS+1];
    /* We configure the listening socket for reading, since poll
     * will tell us that way when a call to 'accept' will succeed */
    tab[0].fd=my_socket;
    tab[0].events=POLLIN;

    char buffer[BUFFER_SIZE];
    while (1) {
        /* We configure the poll array */
        int ndfs=1;
        for (int i=0; i<MAX_CONNECTIONS; i++) {
            if (fds[i]!=-1) {
                tab[ndfs].fd=fds[i];
                tab[ndfs].events=POLLIN;
                ndfs++;
            }
        }
        /* Now we wait for something to happen */
        int n=poll(tab,ndfs,-1);
        for (int i=0; i<ndfs && n>0; i++) {
            if (tab[i].revents&POLLRDHUP) {
                disconnect(tab[i].fd,fds);
            } else if (tab[i].revents&POLLIN) {
                /* There is something ready in this descriptor */
                if (i==0) {
                    /* ACCEPTING A NEW CLIENT CONNECTION */
                    int size=sizeof(addr);
                    int incoming_fd=accept(my_socket,(struct sockaddr*)(&addr),(socklen_t*)(&size));
                    if (incoming_fd==-1) {
                        perror("accept");
                        exit(1);
                    }
                    printf("Connection received from address %s\n",inet_ntoa(addr.sin_addr));
                    const char* MSG="HELLO!\n";
                    write(incoming_fd,MSG,strlen(MSG));
                    /* And we add this new socket to our socket array */
                    int j;
                    for (j=0; j<MAX_CONNECTIONS; j++) {
                        if (fds[j]==-1) {
                            fds[j]=incoming_fd;
                            break;
                        }
                    }
                    if (j==MAX_CONNECTIONS) {
                        fprintf(stderr,"Too many connections\n");
                        close(incoming_fd);
                    }
                } else {
                    /* READ FROM A CLIENT */
                    /* We just have to read something and to answer */
                    int size=read(tab[i].fd,buffer,BUFFER_SIZE-1);
                    if (size<=0) {
                        /* If the connection is closed, we close the socket and
                         * remove it from our descriptor array */
                        disconnect(tab[i].fd,fds);
                    } else {
                        /* We handle the client request */
                        buffer[size]='\0';
                        if (!send_random_data(buffer,tab[i].fd)) {
                            disconnect(tab[i].fd,fds);
                        }
                    }
                }
            }
        }
    }
    close(my_socket);
    return 0;
}
