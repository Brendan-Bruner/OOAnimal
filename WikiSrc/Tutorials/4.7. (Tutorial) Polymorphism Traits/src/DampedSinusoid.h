#ifndef DAMPED_SINUSOID_H_
#define DAMPED_SINUSOID_H_

#include "Class.h"
#include "Sinusoid.h"

/*
 * Even though this class defines its own implementation of the
 * signal method - it does not use the Signal trait again. Its
 * super class uses the Signal trait, this class will override
 * that implementation.
 */
Class(DampedSinusoid) Extends(Sinusoid)
  Data
    double _decay;
  Methods
    void (*setDecay)(DampedSinusoid *, double);
EndClass;

#endif /* DAMPED_SINUSOID_H_ */
