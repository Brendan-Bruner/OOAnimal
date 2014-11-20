/*
 * Crow.h
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
	struct data_Crow data;
	struct vtable_Crow vtable;
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
