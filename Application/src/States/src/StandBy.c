/*
 * StandBy.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "State.h"
#include "StandBy.h"
#include "Satellite.h"

/******************************************************************************
 * Prototypes of super class methods being overridden
 *****************************************************************************/
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
void static pursueMissionObjective_override(StandBy *this,
				    						Satellite *satellite);

/******************************************************************************
 * Concrete method prototypes
 *****************************************************************************/
void static test_concrete(StandBy *this);

/******************************************************************************
 * Class functions
 *****************************************************************************/
void new_StandBy(StandBy *this)
{
	/* Create the super class. */
	new_State(&(this->super));
	this->standByCount = 0;

	/* Assign to the vtable. */
	this->vtable.test =&test_concrete;

	/* Override selected super class functions. */
	this->super.vtable.pursueMissionObjective = (void(*)(State *,Satellite *))&pursueMissionObjective_override;
}

void destroy_StandBy(StandBy *this)
{
	return;
}


void test_StandBy(StandBy *this)
{
	this->vtable.test(this);
}

/******************************************************************************
 * Super class methods being overridden
 *****************************************************************************/
void static pursueMissionObjective_override(StandBy *this,
				    						Satellite *satellite)
{
  printf("stand by pursue mission objective count: %x\n", this->standByCount);
  ++(this->standByCount);
}

/******************************************************************************
 * Concrete methods
 *****************************************************************************/
void static test_concrete(StandBy *standBy)
{
	printf("stand by test\n");
}

