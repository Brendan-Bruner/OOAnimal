/*
 * StandBy.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "State.h"
#include "StandBy.h"
#include "Satellite.h"

void static standByConcrete_pursueMissionObjective(StandBy this,
				    							   Satellite satellite);

static struct StandBy_vtable standBy_vtable =
{
	&standByConcrete_pursueMissionObjective
};

/*
 * ----------------------------------
 * PUBLIC FUNCTIONS
 * ----------------------------------
 */

StandBy newStandBy(void)
{
	/*
	 * Allocate space for a StandBy object.
	 */
	StandBy this = (StandBy) malloc(sizeof(struct StandBy));

	printf("start adr: %p\n"
			"first, State adr: %p\n"
		   "second, vtable adr: %p\n",
		   this, &this->super, &this->vtable);

	/*
	 * Assign the Standby vtable.
	 */
	this->vtable = &standBy_vtable;

	/*
	 * Create the super class.
	 */
	this->super = newState();

	/*
	 * Override selected super class functions.
	 */
	this->super->vtable->pursueMissionObjective = (void(*)(State,Satellite))&standByConcrete_pursueMissionObjective;

	return this;
}

void destroyStandBy(StandBy this)
{
	/*
	 * Destroy the super class.
	 */
	destroyState(this->super);

	/*
	 * Free memory for the class.
	 */
	free(this);
}

void standBy_pursueMissionObjective(StandBy this,
				    				Satellite satellite)
{
	/*
	 * Call the State objects pursueMissionObjective function.
	 */
	this->vtable->pursueMissionObjective(this, satellite);
}

/*
 * ----------------------------------
 * IMPLEMENTATIN OF CLASSES FUNCTIONS
 * ----------------------------------
 */

void static standByConcrete_pursueMissionObjective(StandBy this,
				    							   Satellite satellite)
{
  /*
   * Delay for 4 seconds.
   */
  usleep(4000000);
}

