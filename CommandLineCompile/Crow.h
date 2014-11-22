/* Crow class header file
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

#ifndef CROW_H_
#define CROW_H_

#include "Animal.h"
#include "Bird.h"

/******************************************************************************
 * Class Crow
 *****************************************************************************/
/**
 * This class inherits from Bird.
 * It overrides Animal's location and talk method and Bird's dive method.
 */
typedef struct Crow Crow;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct vtable_Crow
{
	void (* useTool)(Crow *);
};

/******************************************************************************
 * Class data members
 *****************************************************************************/
struct data_Crow
{
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
struct Crow
{
	Bird super;
	struct vtable_Crow vtable;
	struct data_Crow _data;
};

/******************************************************************************
 * Constructor and destructor prototypes
 *****************************************************************************/
/**
 * Constructor.
 * Initializes an object.
 * @param this Object to initialize.
 * @param name The Crow's name.
 */
void new_Crow(Crow *this, char const *name);

/**
 * Destructor.
 * @param this The object to destroy.
 */
void destroy_Crow(Crow *this);

#endif /* CROW_H_ */
