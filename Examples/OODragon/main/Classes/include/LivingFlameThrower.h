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
 *  Created on: 2014-11-19
 *      Author: brendan
 */
/*
 * LivingFlameThrower.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef LIVINGFLAMETHROWER_H_
#define LIVINGFLAMETHROWER_H_

#include "Class.h"
#include "FireBreath.h"

Class(LivingFlameThrower) Extends(Object) Uses(FireBreath)
	int _fuelPower;     
EndClass;

void newLivingFlameThrower( self(LivingFlameThrower) );

#endif /* LIVINGFLAMETHROWER_H_ */
