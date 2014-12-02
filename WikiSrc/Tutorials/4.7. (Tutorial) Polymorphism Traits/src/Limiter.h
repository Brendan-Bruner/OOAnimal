#ifndef LIMITER_H_
#define LIMITER_H_

#include "Class.h"

Class(Limiter)
  Data
    double _max;
    double _min;
  Methods
    void (*setMax)(Limiter *, double);
    void (*setMin)(Limiter *, double);
    double (*limit)(Limiter *, Signal *, double);
EndClass;

#endif /* LIMITER_H_ */
