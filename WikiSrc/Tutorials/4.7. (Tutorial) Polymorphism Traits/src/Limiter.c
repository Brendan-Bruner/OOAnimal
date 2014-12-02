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
