/*
 * StandBy.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */

#include <unistd.h>

#include "State.h"
#include "StandBy.h"
#include "Satellite.h"

/*
 * ----------------------------------
 * VARIABLES
 * ----------------------------------
 */
static struct State_vtable standBy_vtable =
{
  &standBy_pursueMissionObjective
};



/*
 * ----------------------------------
 * FUNCTIONS
 * ----------------------------------
 */
void standBy_new(struct StandBy *this)
{
  this->super.vtable = &standBy_vtable;
  this->x=0;
  this->y=0;
}

void standBy_pursueMissionObjective(struct StandBy *this,
				    struct Satellite *satellite)
{
  /*
   * Delay for 4 seconds.
   */
  usleep(4000000);
}

