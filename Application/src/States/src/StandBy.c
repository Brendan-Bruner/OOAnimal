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

#define NO_CHILD 0

/******************************************************************************
 * Concrete method prototypes
 *****************************************************************************/
void static standByConcrete_pursueMissionObjective(StandBy this,
				    							   Satellite satellite);
void static standByConcrete_test(StandBy this);

/******************************************************************************
 * vtable
 *****************************************************************************/
static struct StandBy_vtable standBy_vtable =
{
	&standByConcrete_pursueMissionObjective,
	&standByConcrete_test
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
StandBy new_StandBy(void)
{
	/* Allocate space for a StandBy object. */
	StandBy this = (StandBy) malloc(sizeof(struct StandBy));
	this->standByCount = 0;

	/* Assign the Standby vtable. */
	this->vtable = &standBy_vtable;

	/* Create the super class. */
	this->super = new_State();

	/* Override selected super class functions and tell it about its child. */
	this->super->vtable->pursueMissionObjective = (void(*)(State,Satellite))&standByConcrete_pursueMissionObjective;
	this->super->child = (void *) this;

	return this;
}

void destroy_StandBy(StandBy this)
{
	/* Destroy the super class. */
	destroy_State(this->super);

	/* Free memory for the class. */
	free(this);
}


void test_StandBy(StandBy this)
{
	if(this->child == NO_CHILD)
	{
		this->vtable->test(this);
	}
	else
	{
		this->vtable->test(this->child);
	}
}

void pursueMissionObjective_StandBy(StandBy this,
				    				Satellite satellite)
{
	/* Call the State objects pursueMissionObjective function. */
	if(this->child == NO_CHILD)
	{
		this->vtable->pursueMissionObjective(this, satellite);
	}
	else
	{
		this->vtable->pursueMissionObjective(this->child, satellite);
	}
}

/******************************************************************************
 * Concrete methods
 *****************************************************************************/
void static standByConcrete_pursueMissionObjective(StandBy this,
				    							   Satellite satellite)
{
  printf("stand by pursue mission objective count: %x\n", this->standByCount);
  ++(this->standByCount);
}

void static standByConcrete_test(StandBy standBy)
{
	printf("stand by test\n");
}

