/*
 * main.c
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
#include "Animal.h"
#include "Bird.h"

void test_animal(Animal *);
void test_bird(Bird *);

int main(int argc, char *argv[])
{
	Animal animal;
	Bird bird;

	new_Animal(&animal);
	new_Bird(&bird);

	test_animal(&animal);
	test_bird(&bird);

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

void test_bird(Bird *bird)
{
	printf("\nBegining of test animal\n****************************\n");

	((Animal *) bird)->vtable.talk(bird);
	((Animal *) bird)->vtable.location(bird);

	printf("I have %i legs after construction\n", ((Animal *) bird)->vtable.getLegs(bird));

	bird->vtable.fly(bird, 89);
	printf("Force of impact after diving from 89 height: %i\n", bird->vtable.dive(bird));

	bird->vtable.fly(bird, 350);
	printf("Force of impact fter diving from 350 height: %i\n", bird->vtable.dive(bird));

	printf("*************************\nDone testing\n");
}
