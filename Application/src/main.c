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

  pursueMissionObjective_State(&standBy, 0);
  test_StandBy(&standBy);

  pursueMissionObjective_State(standByP, 0);
  test_StandBy(standByP);

  pursueMissionObjective_State(&state, 0);

  return 0;
}

