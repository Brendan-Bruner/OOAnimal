/*
 * InnerFire.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef INNERFIRE_H_
#define INNERFIRE_H_

#include "Trait.h"

Trait(InnerFire)
	int (*heatWave)(InnerFire *);
EndTrait;

#endif /* INNERFIRE_H_ */
