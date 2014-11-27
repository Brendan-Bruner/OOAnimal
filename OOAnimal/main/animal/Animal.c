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
 * Set the Animal's name.
 * @param this The Animal object.
 * @param name A pointer to an array of chars - the Animal's name.
 */
static void setName(Animal *this, char const *name)
{
	this->data.name = name;
}

/**
 * Get the Animal's name.
 * @param this The Animal object.
 * @return A pointer to the animals name - a string. Does not
 * guarantee a null terminating character.
 */
static char const * getName(Animal *this)
{
	return this->data.name;
}

/**
 * Make the Animal talk.
 * @param this The Animal object.
 */
static void talk(Animal * this)
{
	printf("Hello, i'm an Animal. My name is %s.\n", this->method.getName(this));
}

/*
 * Set how many the Animal has.
 * @param this The Animal object.
 * @param numLegs How many legs to set.
 */
static void setLegs(Animal *this, int numLegs)
{
	this->data.numLegs = numLegs;
}

/**
 * Get how many legs the animal has.
 * @param this The Animal object.
 * @return The number of legs the Animal has.
 */
static int getLegs(Animal *this)
{
	return this->data.numLegs;
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
Constructor(Animal)
{
	/* Set the Animals method table */
	this->method.setName = &setName;
	this->method.getName = &getName;
	this->method.talk = &talk;
	this->method.setLegs = &setLegs;
	this->method.getLegs = &getLegs;
	this->method.location = &location;

	this->data.numLegs = 0;
}
