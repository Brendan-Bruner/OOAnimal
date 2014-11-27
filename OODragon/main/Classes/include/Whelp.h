/*
 * Dragon.h
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#ifndef DRAGON_H_
#define DRAGON_H_

#include <stdint.h>
#include "Class.h"

Class(Whelp)
	Data
		uint8_t strength;
	Methods
		uint8_t (* attack)(Whelp *);
End;

#endif /* DRAGON_H_ */
