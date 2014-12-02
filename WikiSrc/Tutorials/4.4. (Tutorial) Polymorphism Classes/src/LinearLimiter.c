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

