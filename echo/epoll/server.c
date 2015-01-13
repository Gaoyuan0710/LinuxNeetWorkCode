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
	int num;
	int i;
	int fd;

	memset(buf, 0, MAXSIZE);

	epollFd = epoll_create(FDMAXSIZE);

	addEvent(epollFd, listenfd, EPOLLIN);

	for (;;){
		num = epoll_wait(epollFd, events, EVENTMAXSIZE, -1);

		for (i = 0; i < num; i++){
			fd = events[i].data.fd;

			if ((fd == listenfd) && (events[i].events & EPOLLIN)){
				dealAccept(epollFd, listenfd);
			}
			else if (events[i].events & EPOLLIN){
				dealRead(epollFd, fd, buf);
			}
			else if (events[i].events & EPOLLOUT){
				dealWrite(epollFd, fd, buf);
			}
			else {
				;
			}
		}

	}
}
void dealAccept(int epollFd, int listenfd){
	int clifd;
	struct sockaddr_in cliAddr;
	socklen_t cliAddrLen;

	clifd = accept(listenfd, (struct sockaddr *)&cliAddr, &cliAddrLen);

	if (clifd == -1){
		perror("accept error");
	}
	else{
		printf("New Client %s : %d\n", inet_ntoa(cliAddr.sin_addr), cliAddr.sin_port);
		addEvent(epollFd, clifd, EPOLLIN);
	}
}
void dealRead(int epollFd, int fd, char *buf){
	int readLen;

	readLen = read(fd, buf, MAXSIZE);

	if (readLen == -1){
		perror("read error");
		close(fd);
		deleteEvent(epollFd, fd, EPOLLIN);
		exit(1);
	}
	else if (readLen == 0){
		fprintf(stderr, "client close\n");
		close(fd);
		deleteEvent(epollFd, fd, EPOLLIN);		
	}
	else{
		printf("The message is : %s\n", buf);
		modifyEvent(epollFd, fd, EPOLLOUT);
	}
}

void dealWrite(int epollFd, int fd, char *buf){
	int writeLen;

	writeLen = write(fd, buf, strlen(buf));

	if (writeLen == -1){
		perror("write error");
		close(fd);
		deleteEvent(epollFd, fd, EPOLLOUT);
	}
	else{
		modifyEvent(epollFd, fd, EPOLLIN);
	}
	memset(buf, 0, sizeof(buf));
}
void deleteEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;
	
	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &tmp);
}


void addEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &tmp);
}

void modifyEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;
	
	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &tmp);
}
int main(int argc, char *argv[])
{
	dealWithEpoll(socketPrepare(IP, PORT));

	return EXIT_SUCCESS;
}

