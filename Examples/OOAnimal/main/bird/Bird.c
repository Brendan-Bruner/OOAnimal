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
 * @param self The Bird object.
 * @return How high the Bird is.
 */
static int getHeight(self(Bird))
{
	return self->_height;
}

/**
 * Override
 * Makes the bird talk.
 * @param self The Bird Object.
 */
static void talk(self(Animal))
{
	printf("Hello, i'm a bird. My name is %s.\n", self->getName(self));
}

/**
 * Makes the bird fly above the ground. Negative heights are treated as zero.
 * @param height Distance to fly above the ground.
 * @param self The Bird object.
 */
static void fly(self(Bird), int height)
{
	self->_height = height;
}

/**
 * Makes the bird dive to the ground. Only works if the bird is at least
 * at a height of 300 above the ground. Returns the force the bird hits
 * the ground with.
 * @param self The Bird object.
 * @return The force the bird hits the ground with. Returns 0 if the bird
 * is not high enough to dive.
 */
static int dive(self(Bird))
{
	if(self->_height >= 300)
	{
		int height = self->_height;
		self->fly(self,0);
		return height*2;
	}
	return 0;
}

/******************************************************************************
 * Constructor
 *****************************************************************************/
void newBird(self(Bird))
{
	/* Initialize super class */
  	newAnimal( (Animal *) self );
	
	/* Link Methods */
	LinkMethod(dive);
	LinkMethod(fly);
	LinkMethod(getHeight);

	/* Set Bird's initial height */
	self->fly(self, 2);

	/* Override super class function talk */
	OverrideMethod(Animal, talk);

	/* Set the Birds legs to 2 */
	((Animal *) self)->setLegs((Animal *) self, 2);
}
