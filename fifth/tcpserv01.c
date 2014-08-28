/*
 * =====================================================================================
 *
 *       Filename:  tcpserv01.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月28日 19时55分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERV_PORT 11111
#define LISTENQ 200
#define MAXLINE 10

void str_echo(int socked){
	ssize_t n;
	char buf[MAXLINE];

again:
	while ((n = read(socked, buf, MAXLINE)) >= 0){
		write(socked, buf, n);
	}
	if (n < 0 && errno == EINTR){
		goto again;
	}
	else if(n < 0) {
		printf ("hhhh %s\n", buf);
		printf ("str_echo : read error\n");
	}
}

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);

	for (;;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		if ((childpid = fork()) == 0){
			close(listenfd);
			str_echo(listenfd);
			exit(0);
		}
		close(connfd);
	}

	return EXIT_SUCCESS;
}

