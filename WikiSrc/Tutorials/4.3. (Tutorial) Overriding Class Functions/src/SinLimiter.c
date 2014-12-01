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
  return derived->data._amplitude * sin( 2 * M_PI * derived->data._freq * time);
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
