/*
 * =====================================================================================
 *
 *       Filename:  tcpcli01.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月28日 20时55分45秒
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
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT 9877
#define MAXLINE 10

void str_cli(FILE *fp, int socked){
	char sendline[MAXLINE], recvline[MAXLINE];

	
	while ((fgets(sendline, MAXLINE, fp)) != NULL){
		send(socked, sendline, strlen(sendline), 0);
		
		if (recv(socked, recvline, MAXLINE, 0) == 0){
			printf("str_cli:server terminated prematurely \n");
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2){
		printf("usage:tcpcli <IPaddress>\n");

		return -1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		printf("socket error\n");

		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		printf("inet_pton error\n");

		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		printf("connect error\n");

		perror("connect error");

		return -1;
	}

	str_cli(stdin, sockfd);



	return EXIT_SUCCESS;
}

