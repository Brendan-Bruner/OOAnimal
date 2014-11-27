/* Bird class header file
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

#ifndef BIRD_H_
#define BIRD_H_

#include "Class.h"
#include "Animal.h"

Class(Bird) extends(Animal)
	Data
		int height;
	Methods
		void (* fly)(Bird *, int);
		int (* getHeight)(Bird *);
		int (* dive)(Bird *);
End;

#endif /* BIRD_H_ */
