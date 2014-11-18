#include <stdlib.h>

#include "State.h"
#include "StandBy.h"
#include "Satellite.h"

/*
 * ---------------------------------- 
 * VARIABLES
 * ----------------------------------
 */
static struct state_vtable standBy_vtable =
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
}

void standBy_pursueMissionObjective(struct StandBy *this,
				    struct Satellite *satellite)
{
  /*
   * Delay for 4 seconds.
   */
  delay(4000);
}
