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
#include "LinearLimiter.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static void setSlope(LinearLimiter *this, double slope)
{
  this->data._slope = slope;
}

static double hook(SignalLimiter *this, double time)
{
  LinearLimiter *derived = (LinearLimiter *) this;
  return derived->data._slope * time + this->data._dcBias;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(LinearLimiter)
{
  Super(SignalLimiter);
  LinkMethod(setSlope);
  OverrideMethod(SignalLimiter, hook);
}

