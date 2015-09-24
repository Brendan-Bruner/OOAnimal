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

int main(int argc, char **argv)
{
  Sinusoid mySig;
  newSinusoid(&mySig);

  mySig.setAmplitude(&mySig, 10.0);
  mySig.setFreqHz(&mySig, 1.0);
  mySig.setDCBias(&mySig, 0.0);
  mySig.setPhase(&mySig, 0.0);

  double time;
  for( time = 0.0; time <= 1.0; time += 0.05 )
    {
      /*
       * Below, there are a couple things to note about calling the
       * implementation of a traits function.
       *
       * First, the trait always has the same name, except it ends with a 
       * captial 'T' - mySig.SignalT -. This navigates through the struct,
       * to the the place where the traits function pointers are.
       *
       * Second, the methods used from a trait take a pointer to their
       * trait. Hence, the first argument to the signal function is 
       * a pointer to the Signal trait - &mySig.SignalT -.
       */
      double fx = mySig.SignalT.signal(&mySig.SignalT, time);
      printf("f(%f) = %f\n", time, fx);
    }

  return 0;
}
