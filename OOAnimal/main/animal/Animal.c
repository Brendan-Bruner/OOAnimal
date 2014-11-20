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
static char * getName(Animal *this)
{
	return this->name;
}

static void talk(Animal * this)
{
	printf("Hello, i'm an Animal. My name is %s.\n", this->vtable.getName(this));
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
void new_Animal(Animal *this, char const *name)
{
	this->vtable.getName = &getName;
	this->vtable.talk = &talk;
	this->vtable.setLegs = &setLegs;
	this->vtable.getLegs = &getLegs;
	this->vtable.location = &location;

	this->numLegs = 0;
	this->name = name;
}

void destroy_Animal(Animal *this)
{
	return;
}
