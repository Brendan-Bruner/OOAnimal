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
