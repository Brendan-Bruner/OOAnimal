/*
 * main.c
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
#include "Animal.h"

void test_animal(Animal *);

int main(int argc, char *argv[])
{
	Animal animal;
	new_Animal(&animal);

	test_animal(&animal);

	return 0;
}

void test_animal(Animal *ani)
{
	printf("\nBegining of test animal\n****************************\n");

	ani->vtable.talk(ani);
	ani->vtable.location(ani);

	printf("I have %i legs after construction\n", ani->vtable.getLegs(ani));
	ani->vtable.setLegs(ani, 2);
	printf("Now I have %i legs after setting to 2\n", ani->vtable.getLegs(ani));

	printf("*************************\nDone testing\n");
}
