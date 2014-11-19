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

void static stateConcrete_pursueMissionObjective(State this,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite satellite);

/*
 * State classes vtable.
 */
static struct State_vtable state_vtable =
{
	&stateConcrete_pursueMissionObjective
};

/*
 * ----------------------------------
 * PUBLIC FUNCTIONS
 * ----------------------------------
 *
 * See State.h for documentation.
 */

State newState(void)
{
	/*
	 * Allocate space for a State object
	 */
	State this = (State) malloc(sizeof(struct State));

	/*
	 * Assign the vtable
	 */
	this->vtable = &state_vtable;

	return this;
}

void destroyState(State this)
{
	/*
	 * Free the memory.
	 */
	free(this);
}

void state_pursueMissionObjective(State this,
				  	  	  	  	  Satellite satellite)
{
	/*
	 * Call the State objects pursueMissionObjective function.
	 */
	this->vtable->pursueMissionObjective(this, satellite);
}



/*
 * ----------------------------------
 * IMPLEMENTATION OF CLASS FUNCTIONS
 * ----------------------------------
 */
/**
 * Does nothing. It is up to the child class to implement this function.
 */
void static stateConcrete_pursueMissionObjective(State this,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite satellite)
{
	return;
}

