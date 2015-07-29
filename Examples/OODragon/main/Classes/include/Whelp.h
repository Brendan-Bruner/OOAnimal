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
 * Whelp.h
 *
 *  Created on: 2014-11-27
 *      Author: brendan
 */

#ifndef WHELP_H_
#define WHELP_H_

#include "Class.h"

Class(Whelp) Extends(Object)
	int _strength;
	int _level;
	int _agility;

	int (* attack)( self(Whelp) );
	void (*setLevel)( self(Whelp), int);
	void (*setAgility)( self(Whelp), int);
	int (*getLevel)( self(Whelp) );
	int (*getAgility)( self(Whelp) );
	int (*special)( self(Whelp) );
EndClass;

void newWhelp( self(Whelp) );

#endif /* WHELP_H_ */
