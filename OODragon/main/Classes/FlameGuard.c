/*
 * FlameGuard.c
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#include "FlameGuard.h"

/* Using FireBreath trait */
static int flames(FireBreath *trait)
{
	FlameGuard *this = (FlameGuard *) CastTrait(trait);
	return this->data.magicPower;
}

Constructor(FlameGuard)
{
	newWhelp(this);
	LinkTrait(this, FireBreath);
	this->FireBreathT.flames = &flames;
	this->data.magicPower = 23;
}

