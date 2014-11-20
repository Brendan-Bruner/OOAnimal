/*
 * State.c
 *
 *  Created on: 2014-11-18
 *      Author: brendan
 */
#include <stdlib.h>
#include <stdio.h>

#include "State.h"
#include "Satellite.h"

/******************************************************************************
 * Class methods
 *****************************************************************************/
/**
 * Takes actions to accomplish the satellite's mission. This function
 * is unimplemented and therefore children classes need to make an
 * implementation.
 *@param thisState
 * The object calling the method.
 *@param satellite
 * The Satellite object invoking the method.
 */
void static pursueMissionObjective_State(State *this,
										 Satellite *satellite)
{
	printf("Unimplemented\n");
	return;
}

/******************************************************************************
 * Constructor and destructor
 *****************************************************************************/
void new_State(State *this)
{
	/* Assign the vtable and child */
	this->vtable.pursueMissionObjective = &pursueMissionObjective_State;
}

void destroy_State(State *this)
{
	return;
}
