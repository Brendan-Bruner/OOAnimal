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

	this->attack = &attack;
	this->setLevel = &setLevel;
	this->setAgility = &setAgility;
	this->getLevel = &getLevel;
	this->getAgility = &getAgility;
	this->special = &special;
}
