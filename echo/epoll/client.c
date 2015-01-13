/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月13日 10时04分20秒
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

#include "client.h"

#define IP "127.0.0.1"
#define SERVERPORT 8888
#define EPOLLEVENT 100
#define MAXSIZE 1024
#define FDMAXSIZE 100

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serverAdd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serverAdd, sizeof(serverAdd));

	serverAdd.sin_family = AF_INET;
	serverAdd.sin_port = htons(SERVERPORT);

	inet_pton(AF_INET, IP, &serverAdd.sin_addr);

	connect(sockfd, (struct sockaddr *)&serverAdd, sizeof(serverAdd));

	dealWithEpoll(sockfd);
	return EXIT_SUCCESS;
}
void dealWithEpoll(int listenFd){
	int epollFd;
	struct epoll_event events[EPOLLEVENT];
	char buf[MAXSIZE];
	int ret;
	int fd;
	int i;

	epollFd = epoll_create(FDMAXSIZE);
	addEvent(epollFd, STDIN_FILENO, EPOLLIN);

	for (;;){
		ret = epoll_wait(epollFd, events, EPOLLEVENT, -1);

		for (i = 0; i < ret; i++){
			fd = events[i].data.fd;

			if (events[i].events & EPOLLIN){
				dealRead(epollFd, fd, listenFd, buf);
			}
			else{
				dealWrite(epollFd, fd, listenFd, buf);
			}
		}
	}
}
void dealRead(int epollFd, int fd, int sockfd, char *buf){
	int readLen;

	readLen = read(fd, buf, MAXSIZE);

	if (readLen == -1){
		perror("read error");
		close(fd);
	}

	else{
		if (fd == STDIN_FILENO){
			addEvent(epollFd, sockfd, EPOLLOUT);
		}
		else{
			deleteEvent(epollFd, sockfd, EPOLLIN);
			addEvent(epollFd, STDOUT_FILENO, EPOLLOUT);
		}
	}
}
void dealWrite(int epollFd, int fd, int sockfd, char *buf){
	int writeLen;

	writeLen = write(fd, buf, strlen(buf));

	if (writeLen == -1){
		perror("write error");
		close(fd);
	}
	else{
		if (fd == STDOUT_FILENO){
			deleteEvent(epollFd, fd, EPOLLOUT);
		}
		else{
			modifyEvent(epollFd, fd, EPOLLIN);
		}
	}
	memset(buf, 0, MAXSIZE);
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
