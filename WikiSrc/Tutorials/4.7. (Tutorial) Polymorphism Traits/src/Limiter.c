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
#include "Signal.h"
#include "Limiter.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static void setMax(Limiter *this, double max)
{
  this->data._max = max;
}

static void setMin(Limiter *this, double min)
{
  this->data._min = min;
}

static double limit(Limiter *this, Signal *signal, double time)
{
  double fx = signal->signal(signal, time);
  double max = this->data._max;
  double min = this->data._min;

  if( fx > max ) { return max; }
  if( fx < min) { return min; }
  return fx;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(Limiter)
{
  LinkMethod(setMax);
  LinkMethod(setMin);
  LinkMethod(limit);
}
