/*
 * FireElement.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef FIREELEMENT_H_
#define FIREELEMENT_H_

#include "FireBreath.h"
#include "InnerFire.h"
#include "VolatileCore.h"

Class(FireElement) uses(FireBreath) uses(InnerFire) uses(VolatileCore)
	Data
		int _magic;
	Methods
EndClass;

#endif /* FIREELEMENT_H_ */
