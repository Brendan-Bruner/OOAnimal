/* Animal class header
 * Copyright (C) 2014 Brendan Bruner
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

#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "Class.h"

Class(Animal) Extends(Object)
	int _numLegs;
	char const *_name;

	void (* setName)(self(Animal), char const *);
	char const * (* getName)(self(Animal));
	void (* talk)(self(Animal));
	void (* setLegs)(self(Animal), int);
	int (* getLegs)(self(Animal));
	void (* location)(self(Animal));
EndClass;

void newAnimal( self(Animal) );

#endif /* ANIMAL_H_ */
