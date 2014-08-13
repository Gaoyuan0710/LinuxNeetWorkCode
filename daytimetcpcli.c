/*
 * =====================================================================================
 *
 *       Filename:  daytimetcpcli.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月11日 22时24分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int socked, n;
	char receline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("Please usage : filename <IPdaaress>");
		
		return -1;
	}
	if ((socked = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf ("Socket error\n");

		return -2;
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0 )
	{
		printf ("inet_pton error \n");

		return -3;
	}

	if (connect(socked, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf ("connect error\n");

		perror("connect error");
		return -4;
	}

	while (n = read(socked, receline, MAXLINE) > 0)
	{
		receline[n] = '\0';
		printf("Good\n");
		if (fputs(receline, stdout) == EOF)
		{
			printf ("puts error\n");

			return -5;
		}
	}
	if (n < 0)
	{
		printf ("read error\n");

		return -6;
	}

	return EXIT_SUCCESS;
}

