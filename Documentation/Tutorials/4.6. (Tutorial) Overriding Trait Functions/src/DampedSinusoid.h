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
