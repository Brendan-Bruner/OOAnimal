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
static int attack(Whelp *this)
{
	return this->data._strength;
}

static void setLevel(Whelp *this, int level)
{
	this->data._level = level;
}

static void setAgility(Whelp *this, int agility)
{
	this->data._agility = agility;
}

static int getLevel(Whelp *this)
{
	return this->data._level;
}

static int getAgility(Whelp *this)
{
	return this->data._agility;
}

static int special(Whelp *this)
{
	return this->data._agility + this->data._strength;
}

/****************************************************************************/
/* Constructor																*/
/****************************************************************************/
Constructor(Whelp)
{
	this->data._strength = 3;
	this->data._level = 0;
	this->data._agility = 4;

	LinkMethod(attack);
	LinkMethod(setLevel);
	LinkMethod(setAgility);
	LinkMethod(getLevel);
	LinkMethod(getAgility);
	LinkMethod(special);
}
