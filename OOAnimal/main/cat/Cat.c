/* Cat class source file
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
 *  Created on: 2014-11-20
 *      Author: brendan
 */

#include "Cat.h"
#include <stdio.h>

/******************************************************************************
 * Class methods
 *****************************************************************************/
/**
 * Make the Cat meow
 * @param this Cat object.
 */
static void meow(Cat *this)
{
	printf("MEOW!\n");
}

/**
 * Make the cat talk
 * @param this Cat object.
 */
static void talk(Cat *this)
{
	printf("Hello, i'm a cat. My name is %s\n", ((Animal *) this)->getName(this));
}

/******************************************************************************
 * Constructor
 *****************************************************************************/
Constructor(Cat)
{
	newAnimal(this);

	/* Set Cat vtable */
	this->meow = &meow;

	/* Override Animal's talk method */
	((Animal *) this)->talk = &talk;

	/* Set how many legs a Cat has */
	((Animal *) this)->setLegs(this, 4);
}
