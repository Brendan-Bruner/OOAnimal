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

#include "Animal.h"

/******************************************************************************
 * Class Bird
 *****************************************************************************/
/**
 * Inherits from Animal to describe a bird.
 * Overrides Animal's talk method.
 */
typedef struct Bird Bird;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct vtable_Bird
{
	void (* fly)(Bird *, int);
	int (* getHeight)(Bird *);
	int (* dive)(Bird *);
};

/******************************************************************************
 * Class data members
 *****************************************************************************/
/**
 * @param height how high the bird is above ground.
 */
struct data_Bird
{
	int height;
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
struct Bird
{
	Animal super;
	struct vtable_Bird vtable;
	struct data_Bird _data;
};

/******************************************************************************
 * Constructor and destructor prototypes
 *****************************************************************************/
/**
 * Constructor.
 * Initializes an object.
 * @param this Object to initialize.
 * @param name The Bird's name.
 */
void new_Bird(Bird *this, char const *name);

/**
 * Destructor.
 * @param this The object to destroy.
 */
void destroy_Bird(Bird *this);

#endif /* BIRD_H_ */
