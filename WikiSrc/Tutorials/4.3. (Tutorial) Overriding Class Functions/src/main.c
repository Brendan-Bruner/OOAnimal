#include <stdio.h>
#include "SinLimiter.h"

int main(int argc, char **argv)
{
  SinLimiter mySig;
  newSinLimiter(&mySig);
  
  ((SignalLimiter *) &mySig)->setMax((SignalLimiter *) &mySig, 9.0);
  ((SignalLimiter *) &mySig)->setMin((SignalLimiter *) &mySig, -9.0);
  ((SignalLimiter *) &mySig)->setDCBias((SignalLimiter *) &mySig, 0.0);
  mySig.setAmplitude(&mySig, 10.0);
  mySig.setFreqHz(&mySig, 1.0);

  printf("hook at time = 0.05 is %f\n", ((SignalLimiter *) &mySig)->hook((SignalLimiter *) &mySig, 0.05));

  float i;
  for( i = 0.0; i <= 1.0; i += 0.05 )
    {
      printf("f(%f) = %f\n", i, ((SignalLimiter *) &mySig)->signal((SignalLimiter *) &mySig, i));
    }

  return 0;
}
