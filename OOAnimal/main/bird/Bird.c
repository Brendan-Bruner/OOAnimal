/* Bird class source file
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

#include "Bird.h"
#include <stdio.h>

/******************************************************************************
 * Class methods
 *****************************************************************************/
/**
 * Get how high the bird is.
 * @param this The Bird object.
 * @return How high the Bird is.
 */
static int getHeight(Bird * this)
{
	return this->data.height;
}

/**
 * Override
 * Makes the bird talk.
 * @param this The Bird Object.
 */
static void talk(Bird *this)
{
	printf("Hello, i'm a bird. My name is %s.\n", ((Animal *) this)->getName(this));
}

/**
 * Makes the bird fly above the ground. Negative heights are treated as zero.
 * @param height Distance to fly above the ground.
 * @param this The Bird object.
 */
static void fly(Bird *this, int height)
{
	this->data.height = height;
}

/**
 * Makes the bird dive to the ground. Only works if the bird is at least
 * at a height of 300 above the ground. Returns the force the bird hits
 * the ground with.
 * @param this The Bird object.
 * @return The force the bird hits the ground with. Returns 0 if the bird
 * is not high enough to dive.
 */
static int dive(Bird * this)
{
	if(this->data.height >= 300)
	{
		int height = this->data.height;
		this->fly(this,0);
		return height*2;
	}
	return 0;
}

/******************************************************************************
 * Constructor
 *****************************************************************************/
Constructor(Bird)
{
	/* Initialize super class */
	newAnimal(this);

	/* Set Bird's vtable */
	this->dive = &dive;
	this->fly = &fly;
	this->getHeight = &getHeight;

	/* Set Bird's initial height */
	this->fly(this, 2);

	/* Override super class function talk */
	((Animal *) this)->talk = &talk;

	/* Set the Birds legs to 2 */
	((Animal *) this)->setLegs(this, 2);
}
