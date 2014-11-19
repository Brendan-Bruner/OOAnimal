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
 * Class State
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
 * @param State_vtable Virtual function pointer table for the State class.
 */
struct State
{
  struct State_vtable vtable;
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
/**
 * State constructor.
 * Initializes a State object
 * @param this The state object to initialize.
 */
void new_State(State *this);

/**
 * State destructor.
 * @param this The State object to destroy.
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
