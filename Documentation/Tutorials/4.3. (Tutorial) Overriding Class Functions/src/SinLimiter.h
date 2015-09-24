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
