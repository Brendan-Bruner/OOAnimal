#include <math.h>
#include "Sinusoid.h"
#include "Signal.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/
/* 
 * The first argument to the implementation of the Signal trait's method's is a
 * a pointer to the Trait.
 */
static double signal(Signal *this, double time)
{
  /*
   * Below, the CastTrait macro is used to cast the input - a pointer to a
   * a Signal - to a pointer to a Sinusoid. The CastTrait macro actually
   * does pointer arithmitec in order to cast down to the derived class, therefore,
   * the input pointer (this) has to be put through the CastTrait macro.
   */
  Sinusoid *derived = (Sinusoid *) CastTrait(this);
  
  double amp = derived->data._amplitude;
  double freq = derived->data._freqHz;
  double bias = derived->data._dcBias;

  return amp * sin( 2 * M_PI * freq * time ) + bias;
}

static void setAmplitude(Sinusoid *this, double amp)
{
  this->data._amplitude = amp;
}

static void setFreqHz(Sinusoid *this, double freq)
{
  this->data._freqHz = freq;
}

static void setDCBias(Sinusoid *this, double bias)
{
  this->data._dcBias = bias;
}

static void setPhase(Sinusoid *this, double phase)
{
  this->data._phase = phase;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(Sinusoid)
{
  LinkMethod(setAmplitude);
  LinkMethod(setFreqHz);
  LinkMethod(setDCBias);
  LinkMethod(setPhase);

  /*
   * Below, the LinkTrait macro is used to link the trait to the class. This has 
   * to be done to setup a pointer correctly. If this is not done then the use of
   * the CastTrait macro (see the implementation of signal above) will result
   * in a garbage pointer.
   */
  LinkTrait(Signal);

  /*
   * Below, the LinkTraitMethod macro is used to accomplish the same objective that
   * the LinkMethod macro accomplishes. However, this macro also needs to know what
   * trait the method is defined in.
   * Notice: the name of the function pointer in the Signal trait has to be the same
   * as the implementations name in the source file. This macro expects their names
   * to be the same.
   */
  LinkTraitMethod(Signal, signal);
}
