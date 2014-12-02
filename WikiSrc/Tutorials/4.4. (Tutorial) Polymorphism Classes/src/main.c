#include <stdio.h>
#include "SignalLimiter.h"
#include "SinLimiter.h"
#include "LinearLimiter.h"

#define SIZE 4
#define MID SIZE>>1

void printSignalStream(SignalLimiter **, int, double);

int main(int argc, char **argv)
{
  int iter;
  SignalLimiter *signalArray[SIZE];
  SinLimiter sig0, sig1;
  LinearLimiter sig2, sig3;

  newSinLimiter(&sig0);
  newSinLimiter(&sig1);
  newLinearLimiter(&sig2);
  newLinearLimiter(&sig3);

  signalArray[0] = (SignalLimiter *) &sig0;
  signalArray[1] = (SignalLimiter *) &sig1;
  for( iter = 0; iter < MID; ++iter )
  {
    signalArray[iter]->setMax(signalArray[iter], 3.5*(iter+1));
    signalArray[iter]->setMin(signalArray[iter], -3.5*(iter+1));
    signalArray[iter]->setDCBias(signalArray[iter], 0.0);
    ((SinLimiter *) signalArray[iter])->setFreqHz((SinLimiter *) signalArray[iter], 1.0);
    ((SinLimiter *) signalArray[iter])->setAmplitude((SinLimiter *) signalArray[iter], 5.0*(iter+1));
  }

  signalArray[2] = (SignalLimiter *) &sig2;
  signalArray[3] = (SignalLimiter *) &sig3;
  for(; iter < SIZE; ++iter )
  {
    signalArray[iter]->setMax(signalArray[iter], 15.0*(iter-1));
    signalArray[iter]->setMin(signalArray[iter], (iter+2));
    signalArray[iter]->setDCBias(signalArray[iter], 1.0);
    ((LinearLimiter *) signalArray[iter])->setSlope((LinearLimiter *) signalArray[iter], 10*iter);
  }

  double t;
  for( t = 0.0; t <= 1.0; t += 0.05 )
  {
    printSignalStream(signalArray, SIZE, t);
  }

  return 0;
}

void printSignalStream(SignalLimiter **signalArray, int numSignals, double time)
{
  int i;
  for( i = 0; i < numSignals; ++i)
  {
    printf("f%d(%f) = %f    ", i, time, signalArray[i]->signal(signalArray[i], time));
  }
  printf("\n");
}
