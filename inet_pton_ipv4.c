/*
 * =====================================================================================
 *
 *       Filename:  inet_pton_ipv4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月13日 09时55分23秒
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

int int_pton(int family, const char * strptr, void *addrptr)
{
	if (family == AF_INET)
	{
		struct in_addr in_val;

		if (inet_aton(strptr, &in_val))
		{
			memcpy(addrptr, &in_val, sizeof(struct in_addr));

			return 1;
		}
		return 0;
	}
	errno = EAFNOSUPPORT;
	return -1;
}

