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
void static standByConcrete_test(StandBy this);

static struct StandBy_vtable standBy_vtable =
{
	&standByConcrete_pursueMissionObjective,
	&standByConcrete_test
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

	/*
	 * Assign the Standby vtable.
	 */
	this->vtable = &standBy_vtable;

	/*
	 * Create the super class.
	 */
	this->super = newState();

	/*
	 * Override selected super class functions and tell it about its child.
	 */
	this->super->vtable->pursueMissionObjective = (void(*)(State,Satellite))&standByConcrete_pursueMissionObjective;
	this->super->child = (void *) this;

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


void standBy_test(StandBy this)
{
	this->vtable->test(this);
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
	printf("sleep\n");
  usleep(4000000);
}

void static standByConcrete_test(StandBy standBy)
{
	printf("stand by test\n");
}

