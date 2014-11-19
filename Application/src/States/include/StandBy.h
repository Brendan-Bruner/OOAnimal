/*
 * StandBy.h
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#ifndef STANDBY_H_
#define STANDBY_H_

#include "State.h"
#include "Satellite.h"

/******************************************************************************
 * Class StandBy
 *****************************************************************************/
/**
 * This class inherits from State. Therefore, it is a state. It overrides
 * the super class method pursueMissionObjective_State().
 */
typedef struct StandBy StandBy;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct StandBy_vtable
{
	void (* test)(StandBy *);
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
/**
 * @param super The super class to StandBy. That is, State.
 * @param vtable The virtual function pointer table for a StandBy object.
 * @param standByCount Class data member.
 */
struct StandBy
{
	State super;
	struct StandBy_vtable vtable;
	int standByCount;
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
/**
 * StandBy constructor.
 * Initializes a StandBy object.
 * @param this StandBy object to initialize.
 */
void new_StandBy(StandBy *this);

/**
 * StandBy destructor.
 * @param thisStandBy The StandBy object to destroy.
 */
void destroy_StandBy(StandBy *this);

/**
 * A test function which prints a string to the console.
 * @param this The object calling test_StandBy.
 */
void test_StandBy(StandBy *this);

#endif /* STANDBY_H_ */
