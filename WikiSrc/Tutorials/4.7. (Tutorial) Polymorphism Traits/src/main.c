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
#include "Sinusoid.h"
#include "DampedSinusoid.h"
#include "Linear.h"
#include "Limiter.h"

#define SIZE 3
#define MAX 2.5
#define MIN -6.5

int main(int argc, char **argv)
{
  Signal *signals[SIZE];
  DampedSinusoid dampedSig;
  Sinusoid sinSig;
  Linear linSig;
  Limiter limiter;

  newLimiter(&limiter);
  limiter.setMax(&limiter, MAX);
  limiter.setMin(&limiter, MIN);
  printf("max = %f\nmin = %f\n", MAX, MIN);

  newDampedSinusoid(&dampedSig);
  ((Sinusoid *) &dampedSig)->setAmplitude(((Sinusoid *) &dampedSig), 10.0);
  ((Sinusoid *) &dampedSig)->setFreqHz(((Sinusoid *) &dampedSig), 1.0);
  ((Sinusoid *) &dampedSig)->setDCBias(((Sinusoid *) &dampedSig), 0.0);
  ((Sinusoid *) &dampedSig)->setPhase(((Sinusoid *) &dampedSig), 0.0);
  dampedSig.setDecay(&dampedSig, 5.0);

  newSinusoid(&sinSig);
  sinSig.setAmplitude(&sinSig, 10.0);
  sinSig.setFreqHz(&sinSig, 1.0);
  sinSig.setDCBias(&sinSig, 0.0);
  sinSig.setPhase(&sinSig, 0.0);

  newLinear(&linSig);
  linSig.setSlope(&linSig, 15);
  linSig.setDCBias(&linSig, -7.5);

  signals[0] = &((Sinusoid *) &dampedSig)->SignalT;
  signals[1] = &sinSig.SignalT;
  signals[2] = &linSig.SignalT;

  printf("Damped Sinusoid            Sinusoid                   Linear\n");
  double time;
  int i;
  for( time = 0.0; time <= 1.05; time += 0.05 )
    {
      for( i = 0; i < SIZE; ++i)
	{
	  double fx = limiter.limit(&limiter, signals[i], time);
	  printf("f%d(%f) = %f    ", i, time, fx);
	}
      printf("\n");
    }

  return 0;
}
