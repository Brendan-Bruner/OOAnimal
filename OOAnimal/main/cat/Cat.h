/*
 * Cat.h
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
	struct data_Cat data;
	struct vtable_Cat vtable;
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
