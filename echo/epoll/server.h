/*
 * =====================================================================================
 *
 *       Filename:  server.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月12日 19时46分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int socketPrepare(const char *ip, int port);
int dealWithEpoll(int listenFd);
void addEvent(int epollFd, int fd, int state);
void dealAccept(int epollFd, int listenFd);
void dealRead(int epollFd, int fd, char *buf);

#endif
