/*
 * main.c
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#include "Dragon.h"
#include <stdio.h>

Dragon dragon;

int main(int argc, char **argv)
{
	newDragon(&dragon);
	printf("Dragon's attack did %d damage\n", dragon.method.attack(&dragon));
	return 0;
}
