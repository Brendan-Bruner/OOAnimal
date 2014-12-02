#ifndef SIGNAL_H_
#define SIGNAL_H_

#include "Trait.h"

Trait(Signal)
  double (*signal)(Signal *, double);
EndTrait;

#endif /* SIGNAL_H_ */
