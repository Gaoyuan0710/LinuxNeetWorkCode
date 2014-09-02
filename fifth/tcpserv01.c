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

#define SERV_PORT 9877
#define LISTENQ 0
#define MAXLINE 10

void str_echo(int socked){
	ssize_t n;
	char buf[MAXLINE];

again:
	while ((n = recv(socked, buf, MAXLINE, 0)) >= 0){
		printf("recv %s\n", buf);
		send(socked, buf, n, 0);
	}
	if (n < 0 && errno == EINTR){
		goto again;
	}
	else if(n < 0) {
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

	if (listenfd < 0){
		printf(" socket error \n");
		
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	if ((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0){
		printf("bind error\n");

		return -1;
	}

	
	if (listen(listenfd, LISTENQ) < 0){
		printf("listen error\n");

		return -1;
	}

	for (;;){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		if (connfd < 0){
			printf("accpet error\n");

			return -1;
		}

		if ((childpid = fork()) == 0){
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		else{
			close(connfd);
		}
	}

	return EXIT_SUCCESS;
}

