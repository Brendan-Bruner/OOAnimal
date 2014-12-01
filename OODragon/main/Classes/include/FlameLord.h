/*
 * FlameLord.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef FLAMELORD_H_
#define FLAMELORD_H_

#include "Class.h"
#include "FlameGuard.h"

Class(FlameLord) Extends(FlameGuard)
	Data
	Methods
		int (*reap)(FlameLord *);
EndClass;

#endif /* FLAMELORD_H_ */
