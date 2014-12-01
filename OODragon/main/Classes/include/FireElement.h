/*
 * FireElement.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef FIREELEMENT_H_
#define FIREELEMENT_H_

#include "Class.h"
#include "FireBreath.h"
#include "InnerFire.h"
#include "VolatileCore.h"

Class(FireElement) Uses(FireBreath) Uses(InnerFire) Uses(VolatileCore)
	Data
		int _magic;
	Methods
		int (*getMagic)(FireElement *);
EndClass;

#endif /* FIREELEMENT_H_ */
