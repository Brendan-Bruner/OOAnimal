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

#include "Animal.h"

/******************************************************************************
 * Class Cat
 *****************************************************************************/
/**
 * Cat class which inherits from Animal.
 * This class overrides Animal's talk method.
 */
typedef struct Cat Cat;

/******************************************************************************
 * Class Cat data members
 *****************************************************************************/
struct data_Cat
{
};

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct vtable_Cat
{
	void (* meow)(Cat *);
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
struct Cat
{
	Animal super;
	struct vtable_Cat vtable;
	struct data_Cat _data;
};

/******************************************************************************
 * Constructor and destructor prototypes
 *****************************************************************************/
/**
 * Constructor.
 * Initializes an object.
 * @param this Object to initialize.
 * @param name Name of the Cat.
 */
void new_Cat(Cat *this, char const *name);

/**
 * Destructor.
 * @param this The object to destroy.
 */
void destroy_Cat(Cat *this);

#endif /* CAT_H_ */
