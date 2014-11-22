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
	return this->_data.height;
}

/**
 * Override
 * Makes the bird talk.
 * @param this The Bird Object.
 */
static void talk(Bird *this)
{
	printf("Hello, i'm a bird. My name is %s.\n", ((Animal *) this)->vtable.getName(this));
}

/**
 * Makes the bird fly above the ground. Negative heights are treated as zero.
 * @param height Distance to fly above the ground.
 * @param this The Bird object.
 */
static void fly(Bird *this, int height)
{
	this->_data.height = height;
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
	if(this->_data.height >= 300)
	{
		int height = this->_data.height;
		this->vtable.fly(this,0);
		return height*2;
	}
	return 0;
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
void new_Bird(Bird *this, char const *name)
{
	/* Initialize super class */
	new_Animal(&this->super, name);

	/* Set Bird's vtable */
	this->vtable.dive = &dive;
	this->vtable.fly = &fly;
	this->vtable.getHeight = &getHeight;

	/* Set Bird's initial height */
	this->vtable.fly(this, 2);

	/* Override super class function talk */
	this->super.vtable.talk = (void(*)(Animal *)) &talk;

	/* Set the Birds legs to 2 */
	((Animal *) this)->vtable.setLegs(this, 2);
}

void destroy_Bird(Bird *this)
{
	return;
}
