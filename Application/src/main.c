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

  state = (State) newStandBy();


  printf("Before pursueMissionObject in StandBy state\n");
  standBy_pursueMissionObjective(state, 0);
  printf("After pursueMissionObject in StandBy state\n");

  return 0;
}

