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
