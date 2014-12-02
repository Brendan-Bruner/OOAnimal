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
