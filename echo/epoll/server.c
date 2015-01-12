/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月12日 19时35分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

#define IP "127.0.0.1"
#define PORT 8888
#define MAXSIZE 1024
#define LISTENENQ 5
#define EVENTMAXSIZE 100
#define FDMAXSIZE 1000

int socketPrepare(const char * ip, int port){
	int listenfd;
	struct sockaddr_in serverAdd;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if (-1 == listenfd){
		perror("socket error");
		exit (1);
	}

	bzero(&serverAdd, sizeof(serverAdd));

	serverAdd.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &serverAdd.sin_addr);
	serverAdd.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) == -1){
		perror("bind error");
		exit(1);
	}

	listen(listenfd, LISTENENQ);

	return listenfd;	
}

int dealWithEpoll(int listenfd){
	int epollFd;
	struct epoll_event events[EVENTMAXSIZE];
	char buf[MAXSIZE];

	memset(buf, 0, MAXSIZE);

	epollFd = epoll_create(FDMAXSIZE);

	addEvent(epollFd, listenfd, EPOLLIN);	

}

void addEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &tmp);
}

int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

