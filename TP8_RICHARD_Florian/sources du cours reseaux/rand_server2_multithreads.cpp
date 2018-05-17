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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>


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


void handle_connection(int *fd) {
    char buffer[BUFFER_SIZE];
    int incoming_fd=(*fd);
    const char* MSG="HELLO!\n";
    write(incoming_fd,MSG,strlen(MSG));
    int n,size;
    while (-1!=(size=read(incoming_fd,buffer,BUFFER_SIZE-1))) {
        /* Before doing sscanf, we must truncate the buffer to
         * its actual content */
        buffer[size]='\0';
        if (!send_random_data(buffer,incoming_fd)) {
            break;
        }
    }
    close(incoming_fd);
}


/**
 * This program is a server that listens for numbers as ASCII strings and
 * that returns as many random characters in A-Z as required.
 *
 * This version supports multiple connections, each one being handled
 * by a dedicated thread.
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
    while (1) {
        int size=sizeof(addr);
        /* We block until someone asks for a connection */
        int incoming_fd=accept(my_socket,(struct sockaddr*)(&addr),(socklen_t*)(&size));
        if (incoming_fd==-1) {
            perror("accept");
            exit(1);
        }
        printf("Connection received from address %s\n",inet_ntoa(addr.sin_addr));
        /* We create a thread to handle the connection. This thread must be detached, so
         * that its resources are freed as soon as it terminates */
        pthread_t p;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
        pthread_create(&p,&attr,(void* (*)(void*))handle_connection,&incoming_fd);
    }
    close(my_socket);
    return 0;
}
