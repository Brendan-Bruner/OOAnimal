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
void static standByConcrete_pursueMissionObjective(StandBy *this,
				    							   Satellite *satellite);
void static standByConcrete_test(StandBy *this);

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
void new_StandBy(StandBy *this)
{
	/* Create the super class. */
	new_State(&(this->super));

	this->standByCount = 0;

	/* Assign the Standby vtable. */
	this->vtable = &standBy_vtable;

	/* Override selected super class functions and tell it about its child. */
	this->super.vtable->pursueMissionObjective = (void(*)(State *,Satellite *))&standByConcrete_pursueMissionObjective;
}

void destroy_StandBy(StandBy *this)
{
	return;
}


void test_StandBy(StandBy *this)
{
	this->vtable->test(this);
}

void pursueMissionObjective_StandBy(StandBy *this,
				    				Satellite *satellite)
{
	/* Call the State objects pursueMissionObjective function. */
	this->vtable->pursueMissionObjective(this, satellite);

}

/******************************************************************************
 * Concrete methods
 *****************************************************************************/
void static standByConcrete_pursueMissionObjective(StandBy *this,
				    							   Satellite *satellite)
{
  printf("stand by pursue mission objective count: %x\n", this->standByCount);
  ++(this->standByCount);
}

void static standByConcrete_test(StandBy *standBy)
{
	printf("stand by test\n");
}

