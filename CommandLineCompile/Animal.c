/* Animal class source file
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
#include "Animal.h"
#include <stdio.h>

/******************************************************************************
 * Class methods
 *****************************************************************************/
/**
 * Get the Animal's name.
 * @param this The Animal object.
 * @return A pointer to the animals name - a string. Does not
 * guarantee a null terminating character.
 */
static char * getName(Animal *this)
{
	return this->_data.name;
}

/**
 * Make the Animal talk.
 * @param this The Animal object.
 */
static void talk(Animal * this)
{
	printf("Hello, i'm an Animal. My name is %s.\n", this->vtable.getName(this));
}

/*
 * Set how many the Animal has.
 * @param this The Animal object.
 * @param numLegs How many legs to set.
 */
static void setLegs(Animal *this, int numLegs)
{
	this->_data.numLegs = numLegs;
}

/**
 * Get how many legs the animal has.
 * @param this The Animal object.
 * @return The number of legs the Animal has.
 */
static int getLegs(Animal *this)
{
	return this->_data.numLegs;
}

/**
 * Prints the Animal's location, ie, where it will typically live.
 * @param this The animal object.
 */
static void location(Animal *this)
{
	printf("I live almost every where on Earth\n");
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
void new_Animal(Animal *this, char const *name)
{
	/* Set the Animals vtable */
	this->vtable.getName = &getName;
	this->vtable.talk = &talk;
	this->vtable.setLegs = &setLegs;
	this->vtable.getLegs = &getLegs;
	this->vtable.location = &location;

	this->_data.numLegs = 0;
	this->_data.name = name;
}

void destroy_Animal(Animal *this)
{
	return;
}
