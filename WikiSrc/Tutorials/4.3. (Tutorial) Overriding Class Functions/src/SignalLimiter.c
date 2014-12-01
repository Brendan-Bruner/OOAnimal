#include "SignalLimiter.h"

#define DC_BIAS 0

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

static double hook(SignalLimiter *this, double time)
{
  return DC_BIAS;
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
  this->data._min = DC_BIAS;
  this->data._max = DC_BIAS;
}
