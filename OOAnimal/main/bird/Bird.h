/*
 * Bird.h
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
 * Class data structure
 *****************************************************************************/
/**
 * @param super Super class to Bird.
 * @param height how high the bird is above ground.
 * @param vtable_Bird Function pointer table.
 */
struct Bird
{
	Animal super;
	int height;
	struct vtable_Bird vtable;
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
