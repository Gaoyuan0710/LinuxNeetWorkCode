/*
 * =====================================================================================
 *
 *       Filename:  client.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月13日 10时04分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>

void dealWithEpoll(int listenFd);
void dealRead(int epollFd, int fd, int sockfd, char *buf);
void dealWrite(int epollFd, int fd, int sockfd, char *buf);
void addEvent(int epollFd, int fd, int state);
void deleteEvent(int epollFd, int fd, int state);
void modifyEvent(int epollFd, int fd, int state);

#endif
