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
void static stateConcrete_pursueMissionObjective(State *state,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite *satellite);

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
void new_State(State *this)
{
	/* Assign the vtable and child */
	this->vtable = &state_vtable;
}

void destroy_State(State *this)
{
	return;
}

void pursueMissionObjective_State(State *this,
				  	  	  	  	  Satellite *satellite)
{
	/* Call the State objects pursueMissionObjective function. */
	this->vtable->pursueMissionObjective(this, satellite);
}



/******************************************************************************
 * Concrete methods
 *****************************************************************************/
void static stateConcrete_pursueMissionObjective(State *this,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite *satellite)
{
	return;
}

