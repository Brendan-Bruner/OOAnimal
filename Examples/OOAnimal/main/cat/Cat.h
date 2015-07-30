/* Cat class header file
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
 *  Created on: 2014-11-20
 *      Author: brendan
 */

#ifndef CAT_H_
#define CAT_H_

#include "Class.h"
#include "Animal.h"

Class(Cat) Extends(Animal)
	void (* meow)(self(Cat));
EndClass;

void newCat(self(Cat));

#endif /* CAT_H_ */
