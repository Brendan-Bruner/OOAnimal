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
#include <math.h>
#include "DampedSinusoid.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static double signal(Signal *this, double time)
{
  DampedSinusoid *derived = (DampedSinusoid *) CastTrait(this);

  double amp = ((Sinusoid *) derived)->data._amplitude;
  double freq = ((Sinusoid *) derived)->data._freqHz;
  double dcBias = ((Sinusoid *) derived)->data._dcBias;
  double phase = ((Sinusoid *) derived)->data._phase;
  double decay = derived->data._decay;

  return amp * exp(-decay * time) * sin((2 * M_PI * freq * time) + phase) + dcBias;
}

static void setDecay(DampedSinusoid *this, double decay)
{
  this->data._decay = decay;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(DampedSinusoid)
{
  Super(Sinusoid);
  LinkMethod(setDecay);

  /*
   * Below, to override a traits method the OverrideTraitMethod macro is used.
   * Its first argument is the super class where the trait is being used. The
   * second argument is the name of the trait. The last argument is the name
   * of the method being overrode
   *
   * The LinkTrait macro is not used. This is because the trait
   * is linked to the super class, not this class.
   */
  OverrideTraitMethod(Sinusoid, Signal, signal);
}
