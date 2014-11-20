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
 * Constructor and destructor prototypes
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

#endif /* STATE_H_ */
