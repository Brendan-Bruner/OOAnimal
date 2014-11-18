/*
 * State.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */

#include "State.h"
#include "Satellite.h"

/*
 * ----------------------------------
 * FUNCTIONS
 * ----------------------------------
 *
 * See State.h for documentation.
 */

void state_pursueMissionObjective(struct State *this,
				  struct Satellite *satellite)
{
  this->vtable->pursueMissionObjective(this, satellite);
}

