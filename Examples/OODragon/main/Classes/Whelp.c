/* Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 *
 *  Created on: 2014-11-19
 *      Author: brendan
 */
/*
 * Dragon.c
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */
#include "Whelp.h"

/****************************************************************************/
/* Methods																	*/
/****************************************************************************/
static int attack( self(Whelp) )
{
	return self->_strength;
}

static void setLevel( self(Whelp) , int level)
{
	self->_level = level;
}

static void setAgility( self(Whelp) , int agility)
{
	self->_agility = agility;
}

static int getLevel( self(Whelp) )
{
	return self->_level;
}

static int getAgility( self(Whelp) )
{
	return self->_agility;
}

static int special( self(Whelp) )
{
	return self->_agility + self->_strength;
}

/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
void newWhelp( self(Whelp) )
{
	newObject( (Object *) self );

	self->_strength = 3;
	self->_level = 0;
	self->_agility = 4;

	LinkMethod(attack);
	LinkMethod(setLevel);
	LinkMethod(setAgility);
	LinkMethod(getLevel);
	LinkMethod(getAgility);
	LinkMethod(special);
}
