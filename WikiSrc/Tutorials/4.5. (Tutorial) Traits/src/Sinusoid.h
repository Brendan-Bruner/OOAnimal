/* Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 * 
 * Created: Dec. 2, 2014
 */
#ifndef SINUSOID_H_
#define SINUSOID_H_

#include "Class.h"
#include "Signal.h"

Class(Sinusoid) Uses(Signal)
  Data
    double _amplitude;
    double _freqHz;
    double _dcBias;
    double _phase;
  Methods
    void (*setAmplitude)(Sinusoid *, double);
    void (*setFreqHz)(Sinusoid *, double);
    void (*setDCBias)(Sinusoid *, double);
    void (*setPhase)(Sinusoid *, double);
EndClass;

#endif /* SINUSOID_H_ */
