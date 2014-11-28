/*
 * Whelp.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef WHELP_H_
#define WHELP_H_

#include "Class.h"

Class(Whelp)
	Data
		int _strength;
		int _level;
		int _agility;
	Methods
		int (* attack)(Whelp *);
		void (*setLevel)(Whelp *, int);
		void (*setAgility)(Whelp *, int);
		int (*getLevel)(Whelp *);
		int (*getAgility)(Whelp *);
		int (*special)(Whelp *);
EndClass;

#endif /* WHELP_H_ */
