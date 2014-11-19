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
  State state;
  StandBy standBy;

  standBy = new_StandBy();
  state = STANDBY_TO_STATE(standBy);

  pursueMissionObjective_StandBy(standBy, 0);
  pursueMissionObjective_StandBy(standBy, 0);
  pursueMissionObjective_State(state, 0);
  pursueMissionObjective_State(state, 0);

  test_StandBy(standBy);

  return 0;
}

