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
#include "SignalLimiter.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static void setMax(SignalLimiter *this, double max)
{
  this->data._max = max;
}

static void setMin(SignalLimiter *this, double min)
{
  this->data._min = min;
}

static void setDCBias(SignalLimiter *this, double bias)
{
  this->data._dcBias = bias;
}

static double hook(SignalLimiter *this, double time)
{
  return this->data._dcBias;
}

static double signal(SignalLimiter *this, double time)
{
  double fx = this->hook(this, time);
  
  if( fx < this->data._min )
    {
      return this->data._min;
    }
  if( fx > this->data._max )
    {
      return this->data._max;
    }
  return fx;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(SignalLimiter)
{
  LinkMethod(setMax);
  LinkMethod(setMin);
  LinkMethod(hook);
  LinkMethod(signal);
  LinkMethod(setDCBias);
}
