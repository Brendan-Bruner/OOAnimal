#include <stdio.h>
#include "State.h"
#include "StandBy.h"

int main(int argc, char *argv[])
{
  struct StandBy standByPoly;
  struct State *standBy;

  standBy_new(&standBy);
  standBy = (State *) &standByPoly;

  printf("Before pursueMissionObject in StandBy state\n");
  standBy_pursueMissionObject(standBy);
  printf("After pursueMissionObject in StandBy state\n");

  return 0;
}
