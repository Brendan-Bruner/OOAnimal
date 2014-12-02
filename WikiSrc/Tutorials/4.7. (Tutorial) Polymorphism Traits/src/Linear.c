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
#include "Linear.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
static double signal(Signal *this, double time)
{
  Linear *derived = (Linear *) CastTrait(this);

  double slope = derived->data._slope;
  double bias = derived->data._dcBias;

  return slope * time + bias;
}

static void setSlope(Linear *this, double slope)
{
  this->data._slope = slope;
}

static void setDCBias(Linear *this, double bias)
{
  this->data._dcBias = bias;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(Linear)
{
  LinkMethod(setSlope);
  LinkMethod(setDCBias);
  
  LinkTrait(Signal);
  LinkTraitMethod(Signal, signal);
}
