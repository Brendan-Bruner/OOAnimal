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

  state = newStandBy()->super;

  printf("Before pursueMissionObject in StandBy state\n");
  state_pursueMissionObjective(state, 0);
  printf("After pursueMissionObject in StandBy state\n");

  return 0;
}

