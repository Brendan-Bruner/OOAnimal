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

static double hook(SinLimiter *this, double time)
{
  return this->data._amplitude * sin( 2 * M_PI * this->data._freq * time);
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(SinLimiter)
{
  Super(SignalLimiter);
  LinkMethod(setAmplitude);
  LinkMethod(setFreqHz);
  OverrideMethod(SignalLimiter, hook, double (*)(SignalLimiter *, double));
}
