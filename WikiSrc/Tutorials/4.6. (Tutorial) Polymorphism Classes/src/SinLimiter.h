#ifndef SIN_LIMITER_H_
#define SIN_LIMITER_H_

#include "Class.h"
#include "SignalLimiter.h"

Class(SinLimiter) Extends(SignalLimiter)
  Data
    double _amplitude;
    double _freq;
  Methods
    void (*setAmplitude)(SinLimiter *, double);
    void (*setFreqHz)(SinLimiter *, double);
EndClass;

#endif /* SIN_LIMITER_H_ */
