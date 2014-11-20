/*
 * Bird.c
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
 * Override
 * Makes the bird talk.
 * @param this The Bird Object.
 */
void talk(Bird *this)
{
	printf("Hello, i'm a bird.\n");
}

/**
 * Makes the bird fly above the ground. Negative heights are treated as zero.
 * @param height Distance to fly above the ground.
 * @param this The Bird object.
 */
void fly(Bird *this, int height)
{
	this->height = height;
}

/**
 * Makes the bird dive to the ground. Only works if the bird is at least
 * at a height of 300 above the ground. Returns the force the bird hits
 * the ground with.
 * @param this The Bird object.
 * @return The force the bird hits the ground with. Returns 0 if the bird
 * is not high enough to dive.
 */
int dive(Bird * this)
{
	if(this->height >= 300)
	{
		int height = this->height;
		this->height = 0;
		return height*2;
	}
	return 0;
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
/* TODO: Implement constructor. */
void new_Bird(Bird *this)
{
	/* Initialize super class */
	new_Animal(&this->super);

	/* Set Bird's vtable */
	this->vtable.dive = &dive;
	this->vtable.fly = &fly;

	/* Override super class function talk */
	this->super.vtable.talk = (void(*)(Animal *)) &talk;

	/* Set the Birds legs to 2 */
	((Animal *) this)->vtable.setLegs(this, 2);
}

/* TODO: Implement destructor. */
void destroy_Bird(Bird *this)
{
	return;
}
