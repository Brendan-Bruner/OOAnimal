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
 * @param self The Animal object.
 * @param name A pointer to an array of chars - the Animal's name.
 */
static void setName(self(Animal), char const *name)
{
	MemberOf(Animal);
	self->_name = name;
}

/**
 * Get the Animal's name.
 * @param self The Animal object.
 * @return A pointer to the animals name - a string. Does not
 * guarantee a null terminating character.
 */
static char const * getName(self(Animal))
{
	MemberOf(Animal);
	return self->_name;
}

/**
 * Make the Animal talk.
 * @param self The Animal object.
 */
static void talk(self(Animal))
{
	MemberOf(Animal);
	printf("Hello, i'm an Animal. My name is %s.\n", self->getName(self));
}

/**
 * Set how many the Animal has.
 * @param self The Animal object.
 * @param numLegs How many legs to set.
 */
static void setLegs(self(Animal), int numLegs)
{
	MemberOf(Animal);
	self->_numLegs = numLegs;
}

/**
 * Get how many legs the animal has.
 * @param self The Animal object.
 * @return The number of legs the Animal has.
 */
static int getLegs(self(Animal))
{
	MemberOf(Animal);
	return self->_numLegs;
}

/**
 * Prints the Animal's location, ie, where it will typically live.
 * @param self The animal object.
 */
static void location(self(Animal))
{
	MemberOf(Animal);
	ObjectUnused( );
	printf("I live almost every where on Earth\n");
}

/******************************************************************************
 * Constructor
 *****************************************************************************/
void newAnimal(self(Animal))
{
	MemberOf(Animal);

	/* Initialize super class. */
	newObject( (Object *) self );

	/* Set the Animals method table */
	LinkMethod(setName);
	LinkMethod(getName);
	LinkMethod(talk);
	LinkMethod(setLegs);
	LinkMethod(getLegs);
	LinkMethod(location);

	self->_numLegs = 0;
}
