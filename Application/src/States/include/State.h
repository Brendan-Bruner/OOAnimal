/*
 * State.h
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#include "Satellite.h"

#ifndef STATE_H_
#define STATE_H_

/*
 * State class.
 * This  class implements the state design pattern. It is the super class
 * to all state classes.
 */
typedef struct State* State;

/**
 * Virtual function pointer table for State class.
 */
struct State_vtable
{
	void (* pursueMissionObjective)(State,
									Satellite);
};

/**
 * Data structure representing the State class.
 * @param State_vtable
 * Virtual function pointer table for the State class.
 */
struct State
{
  struct State_vtable *vtable;
};

/*
 * ----------------------------------
 * FUNCTIONS
 * ----------------------------------
 */

/**
 * State constructor.
 * Creates a pointer to a new State object. The new state is dynamically
 * allocated with malloc. Therefore, when finished with the State object
 * the programmer MUST call the objects destructor. destroyState().
 * @return A new State object.
 */
State newState(void);

/**
 * State destructor.
 * Frees the memory allocated for the State object. This must be called when
 * finished with the State object.
 * @param thisState The State object to destroy.
 */
void destroyState(State this);

/**
 * Takes actions to accomplish the satellite's mission. This function
 * is unimplemented and therefore children classes need to make an
 * implementation.
 *@param thisState
 * The object calling the method.
 *@param satellite
 * The Satellite object invoking the method.
 */
void state_pursueMissionObjective(State this,
								  Satellite satellite);

#endif /* STATE_H_ */
