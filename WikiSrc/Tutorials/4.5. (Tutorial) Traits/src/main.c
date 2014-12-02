#include <stdio.h>
#include "Sinusoid.h"

int main(int argc, char **argv)
{
  Sinusoid mySig;
  newSinusoid(&mySig);

  mySig.setAmplitude(&mySig, 10.0);
  mySig.setFreqHz(&mySig, 1.0);
  mySig.setDCBias(&mySig, 0.0);

  double time;
  for( time = 0.0; time <= 1.0; time += 0.05 )
    {
      /*
       * Below, there are a couple things to note about calling the
       * implementation of a traits function.
       * First, the trait always has the same name, except it ends with a 
       * captial 'T'. 
       */
      fx = mySig.SignalT.signal(&mySig.SignalT, time);
      printf("f(%f) = %f\n", time, fx);
    }

  return 0;
}
