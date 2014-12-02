#ifndef LINEAR_LIMITER_H_
#define LINEAR_LIMITER_H_

#include "Class.h"
#include "SignalLimiter.h"

Class(LinearLimiter) Extends(SignalLimiter)
  Data
    double _slope;
  Methods
    void (*setSlope)(LinearLimiter *, double);
EndClass;

#endif /* LINEAR_LIMITER_H_ */

