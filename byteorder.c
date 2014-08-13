/*
 * =====================================================================================
 *
 *       Filename:  byteorder.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月13日 09时27分15秒
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

int main(int argc, char *argv[])
{
	int i;
	union{
		short s;
		char c[sizeof(short)];
	} un;

	un.s = 0x1234;
	printf (" %s:\t", "Computer");

	if (sizeof(short) == 2)
	{
		for (i = 0; i < sizeof(short); i++)
		{
			printf("%x\t", un.c[i]);
		}
		printf("\n");
	}
	else
	{
		printf ("sizeof(short) == %d\n", sizeof(short));
	}
	return EXIT_SUCCESS;
}

