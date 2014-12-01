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

Class(LivingFlameThrower) Uses(FireBreath)
	Data
		int _fuelPower;
	Methods
EndClass;

#endif /* LIVINGFLAMETHROWER_H_ */
