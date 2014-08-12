/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpserv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月12日 12时37分28秒
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
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(INADDR_ANY);

	bind(listenfd, &servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	for (;;){
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.2fs\r\n", ctime(&ticks));
		write(connfd, buf, strlen(buf));

		close(connfd);
	}



	return EXIT_SUCCESS;
}

