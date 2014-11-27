/*
 * FireBreath.h
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#ifndef FIREBREATH_H_
#define FIREBREATH_H_

#include "Trait.h"

Trait(FireBreath)
	int (* flames)(FireBreath *);
EndTrait;

#endif /* FIREBREATH_H_ */
