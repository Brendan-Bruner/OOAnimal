/*
 * State.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#include <stdlib.h>

#include "State.h"
#include "Satellite.h"

void static stateConcrete_pursueMissionObjective(StateConcrete *this,
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
	StateConcrete *this = (StateConcrete *) malloc(sizeof(StateConcrete));

	/*
	 * Assign the vtable
	 */
	this->vtable = &state_vtable;

	/*
	 * Cast the concrete data representation to obscure data and return the
	 * object.
	 */
	return (State) this;
}

void destroyState(State thisState)
{
	/*
	 * Cast the State object given as input to a concrete representation
	 * of the object.
	 */
	StateConcrete *this = (StateConcrete *) thisState;

	/*
	 * Free the memory.
	 */
	free(this);
}

void state_pursueMissionObjective(State thisState,
				  	  	  	  	  Satellite satellite)
{
	/*
	 * Cast the State object given as input to a concrete representation
	 * of the object.
	 */
	StateConcrete *this = (StateConcrete *) thisState;

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
void static stateConcrete_pursueMissionObjective(StateConcrete *this,
	  	  	  	  	  	  	  	  	  	  	  	 Satellite satellite)
{
	return;
}

