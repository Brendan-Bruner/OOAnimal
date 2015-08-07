/* Crow class source file
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

#include "Crow.h"
#include <stdio.h>

/******************************************************************************
 * Class methods
 *****************************************************************************/
/**
 * Makes the crow dive to the ground. Only works if the crow is at least
 * at a height of 50 above the ground. Returns the force the crow hits
 * the ground with.
 * @param self The Crow object.
 * @return The force the crow hits the ground with. Returns 0 if the crow
 * is not high enough to dive.
 */
static int dive(self(Bird))
{
	MemberOf(Crow);
	int height = ((Bird *) self)->getHeight((Bird *) self);
	if( height >= 50)
	{
		((Bird *) self)->fly((Bird *) self, 0);
		return height*2;
	}
	return 0;
}

static void location(self(Animal))
{
	MemberOf(Crow);
	ObjectUnused();
	printf("I live mostly in places with a warmer climate\n");
}

static void talk(self(Animal))
{
	MemberOf(Crow);
	printf("Hello, i'm Crow. My name is %s.\n", ((Animal *) self)->getName((Animal *) self));
}

static void useTool(self(Crow))
{
	MemberOf(Crow);
	printf("%s is using a tool, what a smart crow\n", ((Animal *) self)->getName((Animal *) self));
}

/******************************************************************************
 * Constructor
 *****************************************************************************/
void newCrow( self(Crow) )
{
	MemberOf(Crow);

	/* Initialize super class */
  	newBird( (Bird *) self );

	LinkMethod(useTool);

	/* Override Bird's dive  */
	OverrideMethod(Bird, dive);

	/* Override Animal's talk and location  */
	OverrideMethod(Animal, talk);
	OverrideMethod(Animal, location);
}
