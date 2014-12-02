#ifndef SIGNAL_LIMITER_H_
#define SIGNAL_LIMITER_H_

#include "Class.h"

Class(SignalLimiter)
  Data
    double _max;
    double _min;
    double _dcBias;
  Methods
    void (*setMin)(SignalLimiter *, double);
    void (*setMax)(SignalLimiter *, double);
    void (*setDCBias)(SignalLimiter *, double);
    double (*hook)(SignalLimiter *, double);
    double (*signal)(SignalLimiter *, double);
EndClass;

#endif /* SIGNAL_LIMITER_H_ */
