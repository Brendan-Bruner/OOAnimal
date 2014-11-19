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

  standBy = newStandBy();
  state = STANDBY_TO_STATE(standBy);

  printf("Before pursueMissionObject in StandBy state\n");
  state_pursueMissionObjective(state, 0);
  printf("After pursueMissionObject in StandBy state\n");

  printf("Test func\n");
  standBy_test(STATE_TO_STANDBY(state));
  printf("done test func\n");

  return 0;
}

