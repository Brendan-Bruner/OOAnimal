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
	return this->data._magicPower;
}

/* Override special in super class */
static int special(Whelp *this)
{
	FlameGuard *derived = (FlameGuard *) this;
	return derived->data._magicPower + 9;
}

Constructor(FlameGuard)
{
	Super(Whelp);
	OverrideMethod(Whelp, special);

	LinkTrait(FireBreath);
	LinkTraitMethod(FireBreath, flames);

	this->data._magicPower = 23;
}

