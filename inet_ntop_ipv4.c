/*
 * =====================================================================================
 *
 *       Filename:  inet_ntop_ipv4.c
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  2014年08月13日 10时02分26秒
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
#include <netinet/in.h>
#include <arpa/inet.h>

const char * inet_ntop(int family, const void * addptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *)addptr;

	if (family == AF_INET)
	{
		char temp[INET_ADDRSTRLEN];

		snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		if (strlen(temp) >= len)
		{
			errno = ENOSPC;

			return NULL;
		}
		strcpy(strptr, temp);
		
		return strptr;
	}
	errno = EAFNOSUPPORT;
	return NULL;
}
