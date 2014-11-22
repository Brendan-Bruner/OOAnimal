/*
 * Crow.c
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
 * @param this The Crow object.
 * @return The force the crow hits the ground with. Returns 0 if the crow
 * is not high enough to dive.
 */
static int dive(Crow * this)
{
	int height = ((Bird *) this)->vtable.getHeight(this);
	if( height >= 50)
	{
		((Bird *) this)->vtable.fly(this, 0);
		return height*2;
	}
	return 0;
}

static void location(Crow *this)
{
	printf("I live mostly in places with a warmer climate\n");
}

static void talk(Crow * this)
{
	printf("Hello, i'm Crow. My name is %s.\n", ((Animal *) this)->vtable.getName(this));
}

static void useTool(Crow *this)
{
	printf("%s is using a tool, what a smart crow\n", ((Animal *) this)->vtable.getName(this));
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
void new_Crow(Crow *this, char const *name)
{
	/* Initialize super class */
	new_Bird(&this->super, name);

	/* Set Crow's vtable */
	this->vtable.useTool = &useTool;

	/* Override Bird's dive method. */
	((Bird *) this)->vtable.dive = &dive;

	/* Override Animal's talk and location method. */
	((Animal *) this)->vtable.talk = &talk;
	((Animal *) this)->vtable.location = &location;
}

void destroy_Crow(Crow *this)
{
	return;
}
