/*
 * StandBy.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */

#include <unistd.h>
#include <stdlib.h>

#include "State.h"
#include "StandBy.h"
#include "Satellite.h"

void static standByConcrete_pursueMissionObjective(StandByConcrete *this,
				    							   Satellite satellite);

static struct StandBy_vtable standBy_vtable =
{
	&standByConcrete_pursueMissionObjective
};
static struct State_vtable state_vtable =
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
	StandByConcrete *this = (StandByConcrete *) malloc(sizeof(StandByConcrete));

	/*
	 * Create the super class.
	 */
	this->super = newState();

	/*
	 * Assign the Standby vtable.
	 */
	this->vtable = &standBy_vtable;

	/*
	 * Assign the super classes vtable to override selected super classes
	 * functions.
	 */
	this->super->vtable = &state_vtable;

	/*
	 * Cast the concrete data representation to obscure data and return the
	 * object.
	 */
	return (StandBy) this;
}

void destroyStandBy(StandBy thisStandBy)
{
	/*
	 * Cast the object given as input to a concrete representation
	 * of the object.
	 */
	StandByConcrete *this = (StandByConcrete *) thisStandBy;

	/*
	 * Destroy the super class.
	 */
	destroyState(this->super);

	/*
	 * Free memory for the class.
	 */
	free(this);
}

void standBy_pursueMissionObjective(StandBy thisStandBy,
				    				Satellite satellite)
{
	/*
	 * Cast the object given as input to a concrete representation
	 * of the object.
	 */
	StandByConcrete *this = (StandByConcrete *) thisStandBy;

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

void static standByConcrete_pursueMissionObjective(StandByConcrete *this,
				    							   Satellite satellite)
{
  /*
   * Delay for 4 seconds.
   */
  usleep(4000000);
}

