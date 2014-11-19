/*
 * State.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#include <stdlib.h>
#include <stdio.h>

#include "State.h"
#include "Satellite.h"

#define NO_CHILD 0

/******************************************************************************
 * Concrete method prototypes
 *****************************************************************************/
void static stateConcrete_pursueMissionObjective(State state,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite satellite);

/******************************************************************************
 * vtable.
 *****************************************************************************/
static struct State_vtable state_vtable =
{
	&stateConcrete_pursueMissionObjective
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
State newState(void)
{
	/* Allocate space for a State object */
	State this = (State) malloc(sizeof(struct State));

	/* Assign the vtable and child */
	this->vtable = &state_vtable;
	this->child = NO_CHILD;

	return this;
}

void destroyState(State this)
{
	/* Free the memory. */
	free(this);
}

void state_pursueMissionObjective(State this,
				  	  	  	  	  Satellite satellite)
{
	/* Call the State objects pursueMissionObjective function. */
	this->vtable->pursueMissionObjective(this, satellite);
}



/******************************************************************************
 * Concrete methods
 *****************************************************************************/
void static stateConcrete_pursueMissionObjective(State this,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite satellite)
{
	return;
}

