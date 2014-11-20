/*
 * main.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#include <stdio.h>
#include "State.h"
#include "StandBy.h"

int main(int argc, char *argv[])
{
	/* State object and a standBy object */
  State state;
  State *standByP;
  StandBy standBy;

  /* Initialize standBy and state object */
  new_StandBy(&standBy);
  new_State(&state);
  standByP = (State *)&standBy;

  ((State *) &standBy)->vtable.pursueMissionObjective(&standBy, 0);
  standBy.vtable.test(&standBy);
  //pursueMissionObjective_State(&standBy, 0);
  //test_StandBy(&standBy);

  standByP->vtable.pursueMissionObjective(standByP, 0);
  ((StandBy *) standByP)->vtable.test(standByP);
  //pursueMissionObjective_State(standByP, 0);
  //test_StandBy(standByP);

  state.vtable.pursueMissionObjective(&state,0);
  //pursueMissionObjective_State(&state, 0);

  return 0;
}

