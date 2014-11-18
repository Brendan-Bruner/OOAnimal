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
  struct StandBy standByPoly;
  struct State *standBy;

  standBy_new(&standByPoly);
  standBy = (struct State *) &standByPoly;

  printf("Before pursueMissionObject in StandBy state\n");
  standBy_pursueMissionObjective(standBy, 0);
  printf("After pursueMissionObject in StandBy state\n");

  return 0;
}

