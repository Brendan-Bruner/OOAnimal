/*
 * Animal.h
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_

/******************************************************************************
 * Class Animal
 *****************************************************************************/
/**
 * Animal
 * Describes how an animal talks, how many legs it has, and where it lives.
 */
typedef struct Animal Animal;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct vtable_Animal
{
	void (* talk)(Animal *);
	void (* setLegs)(Animal *, int);
	int (* getLegs)(Animal *);
	void (* location)(Animal *);
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
/**
 * @param numLegs How many legs the animal has.
 * @param vtable virtual function pointer table.
 */
struct Animal
{
	int numLegs;
	struct vtable_Animal vtable;
};

/******************************************************************************
 * Constructor and destructor prototypes
 *****************************************************************************/
/**
 * Constructor.
 * Initializes an object.
 * @param this Object to initialize.
 * @param numLegs How many legs the animal has.
 */
void new_Animal(Animal *this);

/**
 * Destructor.
 * @param this The object to destroy.
 */
void destroy_Animal(Animal *this);

#endif /* ANIMAL_H_ */
