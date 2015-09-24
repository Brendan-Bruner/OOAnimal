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
#include "SinLimiter.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static void setAmplitude(SinLimiter *this, double amp)
{
  this->data._amplitude = amp;
}


static void setFreqHz(SinLimiter *this, double freq)
{
  this->data._freq = freq;
}

static double hook(SignalLimiter *this, double time)
{
  SinLimiter *derived = (SinLimiter *) this;
  return derived->data._amplitude * sin( 2 * M_PI * derived->data._freq * time) + this->data._dcBias;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(SinLimiter)
{
  Super(SignalLimiter);
  LinkMethod(setAmplitude);
  LinkMethod(setFreqHz);
  OverrideMethod(SignalLimiter, hook);
}
