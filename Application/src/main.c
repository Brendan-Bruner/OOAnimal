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
	/* Pointer to state object and a standBy object */
  State *state;
  StandBy standBy;

  /* Initialize standBy object then polymorph it to a State object */
  new_StandBy(&standBy);
  state = (State *) &standBy;

  pursueMissionObjective_StandBy(&standBy, 0);
  pursueMissionObjective_StandBy(&standBy, 0);
  pursueMissionObjective_StandBy(state, 0);
  pursueMissionObjective_StandBy(state, 0);
  pursueMissionObjective_State(state, 0);
  pursueMissionObjective_State(state, 0);
  pursueMissionObjective_State(&standBy, 0);
  pursueMissionObjective_State(&standBy, 0);

  test_StandBy(&standBy);
  test_StandBy(state);

  return 0;
}

