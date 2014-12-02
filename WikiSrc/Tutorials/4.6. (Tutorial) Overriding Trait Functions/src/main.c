/* Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 * 
 * Created: Dec. 2, 2014
 */
#include <stdio.h>
#include "DampedSinusoid.h"

int main(int argc, char **argv)
{
  DampedSinusoid mySig;
  newDampedSinusoid(&mySig);

  ((Sinusoid *) &mySig)->setAmplitude(((Sinusoid *) &mySig), 10.0);
  ((Sinusoid *) &mySig)->setFreqHz(((Sinusoid *) &mySig), 1.0);
  ((Sinusoid *) &mySig)->setDCBias(((Sinusoid *) &mySig), 0.0);
  ((Sinusoid *) &mySig)->setPhase(((Sinusoid *) &mySig), 0.0);
  mySig.setDecay(&mySig, 5.0);

  double time;
  for( time = 0.0; time <= 1.0; time += 0.05 )
    {
      /*
       * Below, there is one thing to note about calling the
       * traits method.
       * The trait is still in the Sinusoid class, thereore, the
       * object has to be cast up to a Sinusoid to get its trait.
       */
      double fx = ((Sinusoid *) &mySig)->SignalT.signal(&((Sinusoid *) &mySig)->SignalT, time);
      printf("f(%f) = %f\n", time, fx);
    }

  return 0;
}
