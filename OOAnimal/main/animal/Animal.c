/*
 * Animal.c
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
#include "Animal.h"
#include <stdio.h>

/******************************************************************************
 * Class methods
 *****************************************************************************/
static void talk(Animal * this)
{
	printf("Hello, i'm an Animal\n");
}

static void setLegs(Animal *this, int numLegs)
{
	this->numLegs = numLegs;
}

static int getLegs(Animal *this)
{
	return this->numLegs;
}

static void location(Animal *this)
{
	printf("I live almost every where on Earth\n");
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
void new_Animal(Animal *this)
{
	this->vtable.talk = &talk;
	this->vtable.setLegs = &setLegs;
	this->vtable.getLegs = &getLegs;
	this->vtable.location = &location;

	this->numLegs = 0;
}

/* TODO: Implement destructor. */
void destroy_Animal(Animal *this)
{
	return;
}
