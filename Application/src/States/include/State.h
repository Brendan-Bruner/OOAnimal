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
 * ----------------------------------
 * DATA STRUCTURES
 * ----------------------------------
 */

/**
 * Virtual function pointer table for the 'abstract' class State.
 * These functions must be implemented by classes inheriting from
 * State.
 *@param pursueMissionObjective
 * A function which will take actions to accomplish the satellites
 * mission objectives. This function takes different actions
 * depending on the state this funciton is called from. Calling
 * this function in a PowerSafe state will perform no action,
 * but calling this fuction from a Detumble state will
 * take actions to correct the satellites spatial orientation.
 */
struct State_vtable
{
  void (* pursueMissionObjective)(struct State *,
				  struct Satellite *);
};

/**
 * Class
 * This class follows the state design pattern. This is the abstract
 * super class of all states.
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
 * Takes actions to accomplish the satellites
 * mission objectives. This function takes different actions
 * depending on the state this funciton is called from. Calling
 * this function in a PowerSafe state will perform no action,
 * but calling this fuction from a Detumble state will
 * take actions to correct the satellites spatial orientation.
 *@param State
 * A pointer to the object calling the method.
 *@param Satellite
 * A pointer to the Satellite invoking the method.
 */
void state_pursueMissionObjective(struct State *,
				  struct Satellite *);

#endif /* STATE_H_ */
