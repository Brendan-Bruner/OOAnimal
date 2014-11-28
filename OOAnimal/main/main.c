/* Demo of OOAnimal standard.
 * Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
#include <stdio.h>
#include "Animal.h"
#include "Bird.h"
#include "Cat.h"
#include "Crow.h"

char const *animalName = "Spooky";
char const *birdName = "Craw";
char const *mutantBirdName = "Mutaeto";
char const *crowName = "Bob";
char const *catsName = "Derp";

void test_animal(Animal *);
void test_bird(Bird *);
void test_crow(Crow *);
void test_cat(Cat *);

int main(int argc, char *argv[])
{
	Animal animal;
	Bird bird, mutantBird;
	Cat cat;
	Crow crow;

	newAnimal(&animal);
	animal.setName(&animal, animalName);

	newBird(&bird);
	((Animal *) &bird)->setName(&bird, birdName);

	newBird(&mutantBird);
	((Animal *) &mutantBird)->setName(&mutantBird, mutantBirdName);
	((Animal *) &mutantBird)->setLegs(&mutantBird, 3);

	newCat(&cat);
	((Animal *) &cat)->setName(&cat, catsName);

	newCrow(&crow);
	((Animal *) &crow)->setName(&crow, crowName);

	test_animal(&animal);
	test_animal(&bird);
	test_animal(&mutantBird);
	test_animal(&cat);
	test_animal(&crow);

	test_cat(&cat);

	test_bird(&bird);
	test_bird(&mutantBird);
	test_bird(&crow);

	test_crow(&crow);

	return 0;
}

void test_animal(Animal *ani)
{
	printf("\nBeginning of test animal\n****************************\n");

	ani->talk(ani);
	ani->location(ani);

	printf("I have %i legs after construction\n", ani->getLegs(ani));

	printf("*************************\nDone testing\n");
}

void test_cat(Cat *cat)
{
	printf("\nBeginning of test cat\n****************************\n");

	((Animal *) cat)->talk(cat);
	((Animal *) cat)->location(cat);

	printf("I have %i legs after construction\n", ((Animal *) cat)->getLegs(cat));

	cat->meow(cat);

	printf("*************************\nDone testing\n");
}

void test_bird(Bird *bird)
{
	printf("\nBeginning of test Bird\n****************************\n");

	((Animal *) bird)->talk(bird);
	((Animal *) bird)->location(bird);

	printf("I have %i legs after construction\n", ((Animal *) bird)->getLegs(bird));

	bird->fly(bird, 89);
	printf("Force of impact after diving from 89 height: %i\n", bird->dive(bird));

	bird->fly(bird, 350);
	printf("Force of impact after diving from 350 height: %i\n", bird->dive(bird));

	printf("*************************\nDone testing\n");
}

void test_crow(Crow *bird)
{
	printf("\nBegining of test Crow\n****************************\n");

	((Animal *) bird)->talk(bird);
	((Animal *) bird)->location(bird);

	printf("I have %i legs after construction\n", ((Animal *) bird)->getLegs(bird));

	((Bird *) bird)->fly(bird, 3);
	printf("Force of impact after diving from 3 height: %i\n", ((Bird *) bird)->dive(bird));

	((Bird *) bird)->fly(bird, 79);
	printf("Force of impact after diving from 79 height: %i\n", ((Bird *) bird)->dive(bird));

	bird->useTool(bird);

	printf("*************************\nDone testing\n");
}
