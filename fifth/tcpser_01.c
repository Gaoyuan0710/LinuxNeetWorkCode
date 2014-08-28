/*
 * =====================================================================================
 *
 *       Filename:  tcpser_01.c
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2014年08月19日 14时55分07秒
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
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define MAXLINE 1024

void str_echo(int socket)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while ( (n = read(socket, buf, MAXLINE)) > 0)
	{
		write(socket, buf, n);
	}
	if (n < 0 && errno == EINTR)
	{
		goto again;
	}
	else if 
	{
		printf("read error\n");

		return -1;
	}
}

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t chilen;
	
	return EXIT_SUCCESS;
}

