#ifndef SINUSOID_H_
#define SINUSOID_H_

#include "Class.h"
#include "Signal.h"

Class(Sinusoid) Uses(Signal)
  Data
    double _amplitude;
    double _freqHz;
    double _dcBias;
  Methods
    void (*setAmplitude)(Sinusoid *, double);
    void (*setFreqHz)(Sinusoid *, double);
    void (*setDCBias)(Sinusoid *, double);
EndClass;

#endif /* SINUSOID_H_ */
