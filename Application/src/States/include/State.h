/*
 * State.h
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#ifndef STATE_H_
#define STATE_H_

#include "Satellite.h"

/******************************************************************************
 * Class typedef
 *****************************************************************************/
/**
 * State class.
 * This  class implements the state design pattern. It is the super class
 * to all state classes.
 */
typedef struct State State;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
/**
 * Virtual function pointer table for State class.
 */
struct State_vtable
{
	void (* pursueMissionObjective)(State *,
									Satellite *);
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
/**
 * Data structure representing the State class.
 * @param State_vtable
 * Virtual function pointer table for the State class.
 * @param child
 * Pointer to child object. This is used to implement polymorphism. When
 * morphing a child class to its super class this keeps a reference to
 * the child class. This is important when calling the child class
 * methods when all you have is its super class
 */
struct State
{
  struct State_vtable *vtable;
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
/**
 * State constructor.
 * Creates a pointer to a new State object. The new state is dynamically
 * allocated with malloc. Therefore, when finished with the State object
 * the programmer MUST call the objects destructor. destroyState().
 * @param this A new State object.
 */
void new_State(State *this);

/**
 * State destructor.
 * Frees the memory allocated for the State object. This must be called when
 * finished with the State object.
 * @param thisState The State object to destroy.
 */
void destroy_State(State *this);

/**
 * Takes actions to accomplish the satellite's mission. This function
 * is unimplemented and therefore children classes need to make an
 * implementation.
 *@param thisState
 * The object calling the method.
 *@param satellite
 * The Satellite object invoking the method.
 */
void pursueMissionObjective_State(State *this,
								  Satellite *satellite);

#endif /* STATE_H_ */
