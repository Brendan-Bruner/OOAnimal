/*
 * main.c
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#include "Whelp.h"
#include "FlameGuard.h"
#include <stdio.h>

FlameGuard flameGuard;
Whelp dragon;

int main(int argc, char **argv)
{
	newFlameGuard(&flameGuard);
	newWhelp(&dragon);
	printf("Dragon's attack did %d damage\n", dragon.attack(&dragon));
	printf("Flame guard's attack did %d damage\n"
			"Flame guard's fire did %d damage\n",
			((Whelp *) &flameGuard)->attack(&flameGuard),
			flameGuard.FireBreathT.flames(&flameGuard.FireBreathT));
	return 0;
}
