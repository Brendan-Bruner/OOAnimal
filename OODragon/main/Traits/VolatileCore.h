/*
 * VolatileCore.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef VOLATILECORE_H_
#define VOLATILECORE_H_

#include "Trait.h"

Trait(VolatileCore)
	int (*explosion)(VolatileCore *);
EndTrait;

#endif /* VOLATILECORE_H_ */
