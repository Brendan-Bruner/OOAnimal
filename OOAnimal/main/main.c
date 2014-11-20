/*
 * main.c
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
#include <stdio.h>
#include "Animal.h"
#include "Bird.h"
#include "Crow.h"

char const *animalName = "Spooky";
char const *birdName = "Craw";
char const *mutantBirdName = "Mutaeto";
char const *crowName = "Bob";

void test_animal(Animal *);
void test_bird(Bird *);
void test_crow(Crow *);

int main(int argc, char *argv[])
{
	Animal animal;
	Bird bird, mutantBird;
	Crow crow;

	new_Animal(&animal, animalName);
	new_Bird(&bird, birdName);
	new_Bird(&mutantBird, mutantBirdName);
	((Animal *) &mutantBird)->vtable.setLegs(&mutantBird, 3);
	new_Crow(&crow, crowName);

	test_animal(&animal);
	test_animal(&bird);
	test_animal(&mutantBird);
	test_animal(&crow);

	test_bird(&bird);
	test_bird(&mutantBird);
	test_bird(&crow);

	test_crow(&crow);

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
	printf("\nBegining of test Bird\n****************************\n");

	((Animal *) bird)->vtable.talk(bird);
	((Animal *) bird)->vtable.location(bird);

	printf("I have %i legs after construction\n", ((Animal *) bird)->vtable.getLegs(bird));

	bird->vtable.fly(bird, 89);
	printf("Force of impact after diving from 89 height: %i\n", bird->vtable.dive(bird));

	bird->vtable.fly(bird, 350);
	printf("Force of impact after diving from 350 height: %i\n", bird->vtable.dive(bird));

	printf("*************************\nDone testing\n");
}

void test_crow(Crow *bird)
{
	printf("\nBegining of test Crow\n****************************\n");

	((Animal *) bird)->vtable.talk(bird);
	((Animal *) bird)->vtable.location(bird);

	printf("I have %i legs after construction\n", ((Animal *) bird)->vtable.getLegs(bird));

	((Bird *) bird)->vtable.fly(bird, 3);
	printf("Force of impact after diving from 3 height: %i\n", ((Bird *) bird)->vtable.dive(bird));

	((Bird *) bird)->vtable.fly(bird, 79);
	printf("Force of impact after diving from 79 height: %i\n", ((Bird *) bird)->vtable.dive(bird));

	bird->vtable.useTool(bird);

	printf("*************************\nDone testing\n");
}
