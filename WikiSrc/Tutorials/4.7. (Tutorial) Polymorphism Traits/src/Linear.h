#ifndef LINEAR_H_
#define LINEAR_H_

#include "Class.h"
#include "Signal.h"

Class(Linear) Uses(Signal)
  Data
    double _slope;
    double _dcBias;
  Methods
    void (*setSlope)(Linear *, double);
    void (*setDCBias)(Linear *, double);
EndClass;

#endif /*LINEAR_H_ */
