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

#define STATE_TO_STANDBY(a) (StandBy)(a)->child
#define STANDBY_TO_STATE(a) (a)->super

/******************************************************************************
 * Class typedef
 *****************************************************************************/
/**
 * StandBy class.
 * This class inherits from State. Therefore, it is a state. The StandBy
 * state is used used to block the calling thread.
 */
typedef struct StandBy * StandBy;

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
/**
 * Virtual function pointer table for StandBy class.
 */
struct StandBy_vtable
{
	void (* pursueMissionObjective)(StandBy,
									Satellite);
	void (* test)(StandBy);
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
/**
 * Data structure representing the StandBy class.
 */
struct StandBy
{
	State super;
	struct StandBy_vtable *vtable;
	void *child;
};

/******************************************************************************
 * Class functions
 *****************************************************************************/
/**
 * StandBy constructor.
 * Creates a pointer to a new StandBy object. The new object is dynamically
 * allocated with malloc. Therefore, when finished with the object
 * the programmer MUST call the objects destructor. destroyStandBy().
 * @return A new StandBy object.
 */
StandBy newStandBy(void);

/**
 * StandBy destructor.
 * Frees the memory allocated for the StandBy object. This must be called when
 * finished with the object.
 * @param thisStandBy The StandBy object to destroy.
 */
void destroyStandBy(StandBy this);

/**
 * Blocks the calling thread for a predefined amount of time. The
 * amount of time blocked for is stored in ROM and is updated
 * as time elapses. Therefore, this method will only block
 * so long as ROM says there is time remaining to block. For example,
 * ROM says to block for 30 minutes. This method is called and
 * the calling thread has been blocked for 27 minutes then a
 * power reset happens. The next time this method is called it
 * will only block the calling thread for 3 minutes.
 *@param thisStandBy
 * The StandBy object this method is being called from
 *@param Satellite
 * The Satellite object invoking this method. The
 * Satellite object is used to get and update the blocking time
 * in ROM.
 */
void standBy_pursueMissionObjective(StandBy this,
				    				Satellite satellite);

/**
 * A test function which prints a string to the console.
 * @param this
 * The object calling.
 */
void standBy_test(StandBy this);

#endif /* STANDBY_H_ */
